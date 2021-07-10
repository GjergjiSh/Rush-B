#include "Publisher.h"

using namespace std;

Publisher::Publisher() {};
Publisher::~Publisher() {};

//Open Publisher Socket
int32_t Publisher::ZMQ_Init_Connection(zmq::context_t context)
{
    try {
        this->zmq_pub_socket = zmq::socket_t(context, zmq::socket_type::pub);
        this->zmq_pub_socket.setsockopt(ZMQ_LINGER, 0);
        this->zmq_pub_socket.bind("tcp://" + this->zqm_pub_transport);
        cout << "[I] [ Control-Center -> Publisher ] ZMQ Connection successfuly initialized - "
             << this->zqm_pub_transport << endl;

    } catch (zmq::error_t& e) {
        cerr << "[E] [ Control-Center -> Publisher ] Failed to initialize ZMQ Connection"
             << e.what() << endl;
        return -1;
    }
    return 0;
}

//Close Publisher Socket
int32_t Publisher::ZMQ_Deinit_Connection()
{
    try {
        this->zmq_pub_socket.close();
        cout << "[I] [ Control-Center -> Publisher ] ZMQ Connection successfuly closed " << endl;
    } catch (zmq::error_t& e) {
        cerr << "[E] [ Control-Center -> Publisher ] Failed to close ZMQ Connection"
             << e.what() << endl;
        return -1;
    }
    return 0;
}

//Send a ZMQ (Topic:String) multipart message
int32_t Publisher::ZMQ_Send(const std::string topic, std::string data)
{
    try {
        //Init message and topic from parameter size
        zmq::message_t z_topic(topic.length());
        zmq::message_t z_data(data.length());

        //Construct message and topic from parameter data
        memcpy(z_topic.data(), topic.data(), topic.length());
        memcpy(z_data.data(), data.data(), data.length());

        //Send message and topic
        this->zmq_pub_socket.send(z_topic, zmq::send_flags::sndmore);
        this->zmq_pub_socket.send(z_data, zmq::send_flags::dontwait);

        //Rebuild message and topic from parameter size
        z_topic.rebuild(topic.size());
        z_data.rebuild(data.length());
    } catch (zmq::error_t& e) {
        cerr << "[E] [ Control-Center -> Publisher ] Failed to send ZMQ Messages"
             << e.what() << endl;
        return -1;
    }
    return 0;
}
