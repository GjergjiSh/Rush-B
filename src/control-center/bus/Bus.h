#ifndef BUS_H
#define BUS_H

#include "PBDriverWish.pb.h"
#include "VideoPipeline.h"
#include "ZMQPipeline.h"
#include <future>


#define LOG_INFO(msg) \
    std::cout << "[I] [ ControlCenter : Bus ] " << msg << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W] [ ControlCenter : Bus ] " << msg << std::endl;
#define LOG_ERROR(msg, err) \
    std::cerr << "[E] [ ControlCenter : Bus ] " << msg << " " << err << std::endl;

class Bus {
public:
    Bus() = default;
    ~Bus() = default;
    int32_t Init();
    int32_t Deinit();

    int32_t ZMQ_Init_Pipeline();
    int32_t ZMQ_Deinit_Pipeline();

    int32_t Video_Init_Pipeline();
    int32_t Video_Deinit_Pipeline();

    int32_t Publish_Driver_Wish( const std::string topic,std::string data);
    std::string Receive_PyDriverWish();

    ZMQPipeline zmq_pipeline;
    VideoPipeline video_sub_pipe;
};

#endif /* BUS_H */