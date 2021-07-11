#ifndef R_SUBSCRIBER_H
#define R_SUBSCRIBER_H

#include <iostream>
#include <zmq.hpp>
#include "PBDriverWish.pb.h"

class Subscriber {

public:
    Subscriber();
    ~Subscriber();

    int32_t ZMQ_Init_Connection();
    int32_t ZMQ_Deinit_Connection();
    PBDriverWish::PBDriverWish ZMQ_Receive();

    std::string zqm_sub_transport;

protected:
    zmq::context_t zmq_sub_context;
    zmq::socket_t zmq_sub_socket;
};

#endif //R_SUBSCRIBER_H