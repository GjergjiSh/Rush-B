#include "RushB.h"
#include <unistd.h>

RushB::RushB(const char* config_path) {
    this->configurator = new Configurator(config_path);
    this->bus.zmq_pipeline.tcp_transport = this->configurator->config_items.at(TCP_TRANSPORT);
    this->bus.serial_transport = this->configurator->config_items.at(SERIAL_PORT);
    this->bus.video_pub_pipe.camera = this->configurator->config_items.at(CAMERA);
    this->bus.video_pub_pipe.camera_subscriber_host = this->configurator->config_items.at(VIDEO_HOST);
    this->bus.video_pub_pipe.camera_subscriber_port = std::__cxx11::stoi(this->configurator->config_items.at(VIDEO_PORT));
};

int32_t RushB::Init()
{
    std::cout << " ================================================================= " << std::endl;
    std::cout << " -------------------------|  Initializing  |---------------------- " << std::endl;
    std::cout << " ================================================================= " << std::endl;
    return this->bus.Init();
}

int32_t RushB::Control_Robot()
{
    PBDriverWish::PBDriverWish driver_wish = this->bus.Receive_Driver_Wish();
    int32_t status = this->bus.arduino_link.Write_To_Port(driver_wish);
/*     //Currently only printing out for testing purpouses
    std::cout << "Top-Servo:" << driver_wish.top_servo() << std::endl;
    std::cout << "Left-Servo:" << driver_wish.left_servo() << std::endl;
    std::cout << "Right-Servo:" << driver_wish.right_servo() << std::endl; */
    usleep(10000);
    return status;
}

int32_t RushB::Deinit()
{
    Kill_Servos();
    return this->bus.Deinit();
    delete this->configurator;
}

void RushB::Kill_Servos()
{
    std::string kill_signal = "!0%0#0&\n";
    this->bus.arduino_link.serial_port->Write(kill_signal);
}