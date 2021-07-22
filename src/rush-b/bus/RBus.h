#ifndef R_BUS_H
#define R_BUS_H

#include "PBDriverWish.pb.h"
#include "RVideoPipeline.h"
#include "RZMQPipeline.h"
#include "ArduinoLink.h"

#define LOG_INFO(msg) \
    std::cout << "[I] [ RushB : Bus ] " << msg << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W] [ RushB : Bus ] " << msg << std::endl;
#define LOG_ERROR(msg, err) \
    std::cerr << "[E] [ RushB : Bus ] " << msg << " " << err << std::endl;


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

    int32_t Arduino_Init_Pipeline();
    int32_t Arduino_Deinit_Pipeline();

    PBDriverWish::PBDriverWish Receive_Driver_Wish();

    std::string tcp_transport;
    std::string serial_transport;
    uint32_t udp_transport;

    ZMQPipeline zmq_pipeline;
    VideoPipeline video_pub_pipe;
    ArduinoLink arduino_link;
};

#endif /* R_BUS_H */