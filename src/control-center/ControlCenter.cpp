#include "ControlCenter.h"

ControlCenter::ControlCenter(const char* config_path){  DRAW_LINE
    this->configurator = std::make_unique<Configurator>(config_path);
    this->active_device = configurator->config_items.at(DEVICE).c_str();
    this->bus.zmq_pipeline.tcp_transport = configurator->config_items.at(TCP_TRANSPORT).c_str();
    this->bus.zmq_pipeline.ipc_interface_transport = configurator->config_items.at(INTERFACE_TRANSPORT).c_str();
    this->bus.video_sub_pipe.port = stoi(configurator->config_items.at(VIDEO_PORT));
    if (configurator->config_items.at(PY_INTERFACE_ACTIVE) == "TRUE") {
        this->bus.zmq_pipeline.py_interface_active = true;
    }
}

int32_t ControlCenter::Init()
{
    std::cout << " ================================================================= " << std::endl;
    std::cout << " -------------------------|  Initializing  |---------------------- " << std::endl;
    std::cout << " ================================================================= " << std::endl;

    if (active_device == "CONTROLLER") this->device = std::make_unique<Controller>();
    else if (active_device == "KEYBOARD") this->device = std::make_unique<Keyboard>();
    else LOG_ERROR("Device type is not supported", "");

    int32_t status = this->device->Initialize_Device(configurator->config_items.at(DEVICE_PATH).c_str());
    status = this->bus.Init() & status;

    return status;
}

int32_t ControlCenter::Control_Robot()
{
    std::string driver_wish;
    int32_t dev_status = 0;
    int32_t s_status = 0;
    int32_t z_status = 0;

    if (this->bus.zmq_pipeline.py_interface_active) {
        driver_wish = this->bus.Receive_PyDriverWish();
        z_status = this->bus.Publish_Driver_Wish("DRIVERWISH", driver_wish);
    } else {
        dev_status = this->device->Process_Input();
        s_status = this->device->driver_wish.SerializeToString(&driver_wish) - 1;
        z_status = this->bus.Publish_Driver_Wish("DRIVERWISH", driver_wish);
        //this->device->Print_Driver_Wish();
        usleep(10000);
    }
    return s_status + z_status + dev_status;
}

int32_t ControlCenter::Deinit()
{
    return this->bus.Deinit();
}