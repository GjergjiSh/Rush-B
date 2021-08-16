#include "Bus.h"

static Bus* bus = nullptr;
static void Extract_Data(GstMapInfo map, const int width, const int height)
{
    unsigned char frame_data[(width * height * 3)];
    memcpy(frame_data, map.data, sizeof(frame_data));

    std::scoped_lock<std::mutex> lock(bus->v_mutex);
    bus->last_appsink_frame = cv::Mat(height, width, CV_8UC3, (uchar*)frame_data, cv::Mat::AUTO_STEP);

    if (bus->last_appsink_frame.data) {
        if (!bus->object_detection_active) {
            bus->Display_Video();
        }
    }
}

int32_t Bus::Init()
{
    if (this->object_detection_active) {
        Init_Object_Detector();
    }

    int32_t status = ZMQ_Init_Pipeline();
    status = Video_Init_Pipeline() & status;
    if (status == 0) {LOG_INFO("Bus succcessfuly initialzed");
    } else {LOG_ERROR("Bus failed to initialize", "");}
    return status;
}

int32_t Bus::Deinit()
{
    int32_t status = ZMQ_Deinit_Pipeline();
    status = Video_Deinit_Pipeline() & status;

    if (status == 0) {
        if (this->detection_thread.joinable()) {
            this->detection_thread.detach();
        }
        LOG_INFO("Bus succcessfuly deinitialzed");
    } else {LOG_ERROR("Bus failed to deinitialize", ""); }

    return status;
}

std::string Bus::Receive_PyDriverWish()
{
    int32_t recv = 0;
    zmq::message_t z_message;
    zmq::pollitem_t subscriber = {this->zmq_pipeline.pipe.dw_sub_socket, 0, ZMQ_POLLIN, 0};
    std::string driver_wish;

    try {
        zmq::poll(&subscriber, 1, -1);
        if (subscriber.revents & ZMQ_POLLIN) {
            recv = this->zmq_pipeline.pipe.dw_sub_socket.recv(&z_message);
            if (recv > 0) {
                driver_wish = static_cast<char*>(z_message.data()), z_message.size();
            }
        }
    } catch (zmq::error_t& e) {
        LOG_ERROR("Failed to receive driver wish", e.what());
    }
    return driver_wish;
}

int32_t Bus::Publish_Driver_Wish(
    const std::string topic,
    std::string data)
{
    try {
        zmq::message_t z_topic(topic.length());
        zmq::message_t z_data(data.length());
        memcpy(z_topic.data(), topic.data(), topic.length());
        memcpy(z_data.data(), data.data(), data.length());
        this->zmq_pipeline.pipe.dw_pub_socket.send(z_topic, zmq::send_flags::sndmore);
        this->zmq_pipeline.pipe.dw_pub_socket.send(z_data, zmq::send_flags::dontwait);
        z_topic.rebuild(topic.size());
        z_data.rebuild(data.length());
    } catch (zmq::error_t& e) {
        LOG_ERROR("Failed to send ZMQ message over TCP connection", e.what());
        return -1;
    }
    return 0;
}

void Bus::Display_Video()
{
    cv::imshow("Control Center", this->last_appsink_frame);
    cv::waitKey(1);
}

int32_t Bus::Video_Init_Pipeline()
{
    int32_t status = this->video_sub_pipe.Construct_Pipeline();
    if (status == 0) {
        bus = this;
        this->video_sub_pipe.pipeline->Extract_Data =  Extract_Data;
        status = this->video_sub_pipe.Set_Pipeline_State_Playing() & status;
    }
    return status;
}

void Bus::Init_Object_Detector()
{
    this->object_detector.Init_Model();
    this->object_detector.Load_Labels();

    this->detection_thread = std::thread([this]() {
        while (1) { Invoke_Detector();}
    });
}

void Bus::Invoke_Detector()
{
    std::scoped_lock<std::mutex> lock(this->p_mutex);
    if (this->last_appsink_frame.data) {
        this->detection_results = this->object_detector.Detect(last_appsink_frame);
        Display_Video();
    }
}

int32_t Bus::Video_Deinit_Pipeline()
{
    return this->video_sub_pipe.Destroy_Pipeline();
}

int32_t Bus::ZMQ_Init_Pipeline()
{
    return this->zmq_pipeline.Construct_Pipeline();
}

int32_t Bus::ZMQ_Deinit_Pipeline()
{
    return this->zmq_pipeline.Destroy_Pipeline();
}