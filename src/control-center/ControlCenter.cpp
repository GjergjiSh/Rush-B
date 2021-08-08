#include "ControlCenter.h"

ControlCenter::ControlCenter(const char* config_path){
    this->configurator = new Configurator(config_path);
    this->active_device = configurator->config_items.at(DEVICE).c_str();
    this->bus.zmq_pipeline.tcp_transport = configurator->config_items.at(TCP_TRANSPORT).c_str();
    this->bus.zmq_pipeline.ipc_interface_transport = configurator->config_items.at(INTERFACE_TRANSPORT).c_str();
    this->bus.zmq_pipeline.ipc_device_transport = "devicetransport";
    this->bus.video_sub_pipe.port = stoi(configurator->config_items.at(VIDEO_PORT));
}

int32_t ControlCenter::Init()
{
    std::cout << " ================================================================= " << std::endl;
    std::cout << " -------------------------|  Initializing  |---------------------- " << std::endl;
    std::cout << " ================================================================= " << std::endl;
    if (active_device == "CONTROLLER") this->device = new Controller();
    else this->device = new Keyboard();

    int32_t device_status = this->device->Initialize_Device(configurator->config_items.at(DEVICE_PATH).c_str());
    int32_t bus_status = this->bus.Init();
    return bus_status + device_status;
}

int32_t ControlCenter::Control_Robot()
{
    std::string driver_wish;

    int32_t dev_status = this->device->Process_Input();
    int32_t s_status = this->device->driver_wish.SerializeToString(&driver_wish) - 1;
    int32_t z_status = this->bus.Publish_Driver_Wish("CONTROLLER", driver_wish);
    //this->device->Print_Driver_Wish();
    usleep(10000);
    return s_status + z_status + dev_status;
}

int32_t ControlCenter::Deinit()
{
    return this->bus.Deinit();
    delete this->device;
    delete this->configurator;
}