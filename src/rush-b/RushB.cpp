#include "RushB.h"
#include <unistd.h>

RushB::RushB() {};
RushB::~RushB() {};

int32_t RushB::Init()
{
    { //TODO:Temporarily hardcoded, needs to be read from cfg
        this->bus.zmq_pipeline.tcp_transport = "127.0.0.1:5001";
        this->bus.serial_transport = "/dev/ttyACM0";
        // this->bus.video_pub_pipe.pipeline->parameters.camera = "/dev/video0";
        // this->bus.video_pub_pipe.pipeline->parameters.sink_param.host = "127.0.0.1";
        // this->bus.video_pub_pipe.pipeline->parameters.sink_param.port = 5000;
        // this->bus.video_pub_pipe.pipeline->parameters.x264_param.bitrate = 2000;
        // this->bus.video_pub_pipe.pipeline->parameters.x264_param.speed_preset = 1;
        // this->bus.video_pub_pipe.pipeline->parameters.x264_param.tune = 4;
    }
    return this->bus.Init();
}

int32_t RushB::Control_Robot()
{
    PBDriverWish::PBDriverWish driver_wish = this->bus.Receive_Driver_Wish();
    int32_t status = this->bus.arduino_link.Write_To_Port(driver_wish);
    //Currently only printing out for testing purpouses
    // std::cout << "Top-Servo:" << driver_wish.top_servo() << std::endl;
    // std::cout << "Left-Servo:" << driver_wish.left_servo() << std::endl;
    // std::cout << "Right-Servo:" << driver_wish.right_servo() << std::endl;
    usleep(10000);
    return status;
}

int32_t RushB::Deinit()
{
    return this->bus.Deinit();
}