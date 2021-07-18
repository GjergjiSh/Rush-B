#include "ZMQPipeline.h"


void ZMQPipeline::Construct_Sockets()
{
    this->pipe.dw_pub_socket = zmq::socket_t(this->pipe.zmq_context, zmq::socket_type::pub);
    this->pipe.video_pub_socket = zmq::socket_t(this->pipe.zmq_context, zmq::socket_type::pub);
    this->pipe.dw_sub_socket = zmq::socket_t(this->pipe.zmq_context, zmq::socket_type::sub);
}

void ZMQPipeline::Configure_Sockets()
{
    this->pipe.dw_pub_socket.setsockopt(ZMQ_LINGER, 0);
    this->pipe.dw_pub_socket.bind("tcp://" + this->tcp_transport);
    this->pipe.video_pub_socket.setsockopt(ZMQ_LINGER, 0);
    this->pipe.video_pub_socket.bind("ipc://" + this->ipc_interface_transport);
    this->pipe.dw_sub_socket.setsockopt(ZMQ_LINGER, 0);
    this->pipe.dw_sub_socket.setsockopt(ZMQ_SUBSCRIBE, "DW", 2);
    this->pipe.dw_sub_socket.connect("ipc://" + this->ipc_interface_transport);
}

void ZMQPipeline::Close_Sockets()
{
    this->pipe.dw_pub_socket.close();
    this->pipe.dw_sub_socket.close();
    this->pipe.video_pub_socket.close();
}

int32_t ZMQPipeline::Construct_Pipeline()
{
    try {
        this->pipe.zmq_context = zmq::context_t(1);
        Construct_Sockets();
        Configure_Sockets();
        ZLOG_INFO("ZMQ Pipeline constructed : "+this->tcp_transport);
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