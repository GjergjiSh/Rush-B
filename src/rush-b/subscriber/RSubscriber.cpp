#include "RSubscriber.h"

using namespace std;

Subscriber::Subscriber() {};
Subscriber::~Subscriber() {};

//Open Subscriber Socket
int32_t Subscriber::ZMQ_Init_Connection()
{
    try {
        this->zmq_sub_context = zmq::context_t(1);
        this->zmq_sub_socket = zmq::socket_t(this->zmq_sub_context, zmq::socket_type::sub);
        this->zmq_sub_socket.setsockopt(ZMQ_SUBSCRIBE, "CONTROLLER", 10);
        this->zmq_sub_socket.setsockopt(ZMQ_SUBSCRIBE, "KEYBOARD", 8);
        this->zmq_sub_socket.setsockopt(ZMQ_LINGER, 0);
        this->zmq_sub_socket.connect("tcp://" + this->zqm_sub_transport);
        cout << "[I] [ Rush-B -> Subscriber ] ZMQ Connection Successfuly Initialized - "
             << this->zqm_sub_transport << endl;

    } catch (zmq::error_t& e) {
        cerr << "[E] [ Rush-B -> Subscriber ] Failed to Initialize ZMQ Connection "
             << e.what() << endl;
        return -1;
    }
    return 0;
}

//Close Subscriber Socket
int32_t Subscriber::ZMQ_Deinit_Connection()
{
    try {
        this->zmq_sub_socket.close();
        zmq_sub_context.close();
        cout << "[I] [ Rush-B -> Subscriber ] ZMQ Connection Successfuly Closed " << endl;
    } catch (zmq::error_t& e) {
        cerr << "[E] [ Rush-B -> Subscriber ] Failed To Close ZMQ Connection "
             << e.what() << endl;
        return -1;
    }
    return 0;
}

//Receives a ZMQ (Topic:String) multipart message and converts it to DriverWish obj
PBDriverWish::PBDriverWish Subscriber::ZMQ_Receive()
{
    int32_t recv = 0;
    zmq::message_t z_topic;
    zmq::message_t z_message;
    zmq::pollitem_t subscriber = { this->zmq_sub_socket, 0, ZMQ_POLLIN, 0 };
    PBDriverWish::PBDriverWish pb_driver_wish;

    try {
        zmq::poll(&subscriber, 1, 0);

        if (subscriber.revents & ZMQ_POLLIN) {
            recv = this->zmq_sub_socket.recv(&z_topic, ZMQ_RCVMORE);
            recv = this->zmq_sub_socket.recv(&z_message) && recv;

            if (recv > 0) {
                string driver_wish(static_cast<char*>(z_message.data()), z_message.size());
                pb_driver_wish.ParseFromString(driver_wish);
            }
        }

    } catch (zmq::error_t& e) {
        cerr << "[E] [ Rush-B -> Subscriber ] Failed To Receive ZMQ Messages "
             << e.what() << endl;
    }
    return pb_driver_wish;
}