#include <iostream>
#include <zmq.hpp>

#define ZLOG_INFO(msg) \
    std::cout << "[I] [ Bus : ZMQPipeline  ] " << msg << std::endl;
#define ZLOG_WARNING(msg) \
    std::cerr << "[W] [ Bus : ZMQPipeline ] " << msg << std::endl;
#define ZLOG_ERROR(msg, err) \
    std::cerr << "[E] [ Bus : ZMQPipeline  ] " << msg << " " << err << std::endl;

typedef struct
{
    zmq::context_t zmq_context;
    zmq::socket_t dw_sub_socket;
} tZMQPipeline;

class ZMQPipeline {
public:
    ZMQPipeline() = default;
    ~ZMQPipeline() = default;
    int32_t Construct_Pipeline();
    int32_t Destroy_Pipeline();

    std::string tcp_transport;
    tZMQPipeline pipe;

private:
    void Construct_Sockets();
    void Configure_Sockets();
    void Close_Sockets();
};
