#include "RBus.h"

int32_t Bus::Init()
{
    int32_t status = 0;
    status = ZMQ_Init_Pipeline();
    if (status == 0) status = Video_Init_Pipeline();
    if (status == 0) status = Arduino_Init_Pipeline();
    if (status == 0) {LOG_INFO("Bus succcessfuly initialzed");
    } else { LOG_ERROR("Bus failed to initialize", ""); }
    return status;
}

int32_t Bus::Deinit()
{
    int32_t status = 0;
    status = ZMQ_Deinit_Pipeline();
    if (status == 0) status = Video_Deinit_Pipeline();
    if (status == 0) {status = Arduino_Deinit_Pipeline();}
    return status;
}

int32_t Bus::Video_Init_Pipeline()
{
    int32_t status = this->video_pub_pipe.Construct_Pipeline();
    if (status == 0) status = this->video_pub_pipe.Set_Pipeline_State_Playing();
    return status;
}

int32_t Bus::Video_Deinit_Pipeline()
{
    return this->video_pub_pipe.Destroy_Pipeline();
}

int32_t Bus::ZMQ_Init_Pipeline()
{
    return this->zmq_pipeline.Construct_Pipeline();
}

int32_t Bus::ZMQ_Deinit_Pipeline()
{
    return this->zmq_pipeline.Destroy_Pipeline();
}

int32_t Bus::Arduino_Init_Pipeline()
{
    return this->arduino_link.Init_Serial_Port(this->serial_transport);
}

int32_t Bus::Arduino_Deinit_Pipeline()
{
    return this->arduino_link.Deinit_Serial_Port();
}

PBDriverWish::PBDriverWish Bus::Receive_Driver_Wish()
{
    int32_t recv = 0;
    zmq::message_t z_topic;
    zmq::message_t z_message;
    zmq::pollitem_t subscriber = { this->zmq_pipeline.pipe.dw_sub_socket, 0, ZMQ_POLLIN, 0 };
    PBDriverWish::PBDriverWish pb_driver_wish;

    try {
        zmq::poll(&subscriber, 1, -1);
        if (subscriber.revents & ZMQ_POLLIN) {
            recv = this->zmq_pipeline.pipe.dw_sub_socket.recv(&z_topic, ZMQ_RCVMORE);
            recv = this->zmq_pipeline.pipe.dw_sub_socket.recv(&z_message) && recv;
            if (recv > 0) {
                std::string driver_wish(static_cast<char*>(z_message.data()), z_message.size());
                pb_driver_wish.ParseFromString(driver_wish);
            } else {
                LOG_WARNING("Unknown prefix for the driver wish");
            }
        }
    } catch (zmq::error_t& e) {
        LOG_ERROR("Failed to receive driver wish", e.what());
    }
    return pb_driver_wish;
}