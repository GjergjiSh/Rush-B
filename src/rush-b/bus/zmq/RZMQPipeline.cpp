#include "RZMQPipeline.h"

void ZMQPipeline::Construct_Sockets()
{
    this->pipe.dw_sub_socket = zmq::socket_t(this->pipe.zmq_context, zmq::socket_type::sub);
}

void ZMQPipeline::Configure_Sockets()
{
    this->pipe.dw_sub_socket.setsockopt(ZMQ_SUBSCRIBE, "DRIVERWISH", 10);
    this->pipe.dw_sub_socket.setsockopt(ZMQ_LINGER, 0);
    this->pipe.dw_sub_socket.connect("tcp://" + this->tcp_transport);
}

void ZMQPipeline::Close_Sockets()
{
    this->pipe.dw_sub_socket.close();
}

int32_t ZMQPipeline::Construct_Pipeline()
{
    try {
        this->pipe.zmq_context = zmq::context_t(1);
        Construct_Sockets();
        Configure_Sockets();
        ZLOG_INFO("ZMQ Pipeline constructed : " + this->tcp_transport);
    } catch (zmq::error_t& e) {
        ZLOG_ERROR("Failed to construct ZMQ Pipeline", e.what());
        return -1;
    }
    return 0;
}

int32_t ZMQPipeline::Destroy_Pipeline()
{
    try {
        Close_Sockets();
        this->pipe.zmq_context.close();
    } catch (zmq::error_t& e) {
        ZLOG_ERROR("Failed to destory ZMQ Pipeline", e.what());
        return -1;
    }
    return 0;
}