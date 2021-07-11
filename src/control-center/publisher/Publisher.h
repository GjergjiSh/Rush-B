#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <zmq.hpp>
#include <iostream>

class Publisher {

public:
    Publisher();
    ~Publisher();

    int32_t ZMQ_Init_Connection();
    int32_t ZMQ_Deinit_Connection();
    int32_t ZMQ_Send(const std::string topic, std::string data);

    std::string zqm_pub_transport;

protected:
    zmq::context_t zmq_pub_context;
    zmq::socket_t zmq_pub_socket;

};

#endif //PUBLISHER_H