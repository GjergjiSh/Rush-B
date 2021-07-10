#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <zmq.hpp>
#include <iostream>

class Publisher {

public:
    Publisher();
    ~Publisher();

    int32_t ZMQ_Init_Connection(zmq::context_t context);
    int32_t ZMQ_Deinit_Connection();
    int32_t ZMQ_Send(const std::string topic, std::string data);

protected:
    zmq::socket_t zmq_pub_socket;
    std::string zqm_pub_transport;
};

#endif //PUBLISHER_H