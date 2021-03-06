#include "Bus.h"

int32_t Bus::Init()
{
    int32_t status = 0;
    status = ZMQ_Init_Pipeline();
    if (status == 0) status = Video_Init_Pipeline();
    if (status == 0) {LOG_INFO("Bus succcessfuly initialzed");
    } else {LOG_ERROR("Bus failed to initialize", ""); }
    return status;
}

int32_t Bus::Deinit()
{
    int32_t status = 0;
    status = ZMQ_Deinit_Pipeline();
    if (status == 0) {status = Video_Deinit_Pipeline();}
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

int32_t Bus::Video_Init_Pipeline()
{
    int32_t status = this->video_sub_pipe.Construct_Pipeline();
    if (status == 0) status = this->video_sub_pipe.Set_Pipeline_State_Playing();
    if (status == 0) {this->video_sub_pipe.Start_Gloop();}
    return status;
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