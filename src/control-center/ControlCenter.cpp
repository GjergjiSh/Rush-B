#include "ControlCenter.h"

int32_t ControlCenter::Connect_Device()
{
    switch (this->active_device) {
    case CONTROLLER:
        return this->controller.Initialize_Device();
    case KEYBOARD:
        return this->keyboard.Initialize_Device();
    default:
        std::cerr << "[E] [ Control-Center -> Connect Device ] Unaccepted parameter for the active device: "
                  << this->active_device << std::endl;
    }
    return -1;
}

int32_t ControlCenter::Init()
{
    { //TODO: The code in this scope temporarily hardcoded. these items should be configurable through the control-center.cfg file
        this->controller.device_path = "/dev/input/by-id/usb-Inno_GamePad.._Inno_GamePad.._0000001-joystick";
        this->active_device = CONTROLLER;
        this->bus.udp_transport = 5000;
        this->bus.zmq_pipeline.tcp_transport = "0.0.0.0:5001";
        this->bus.zmq_pipeline.ipc_interface_transport = "interfacetransport";
        this->bus.zmq_pipeline.ipc_device_transport = "devicetransport";
    }
    int32_t bus_status = this->bus.Init();
    int32_t device_status = this->Connect_Device();
    return bus_status + device_status;
}

int32_t ControlCenter::Control_Robot()
{
    std::string driver_wish;
    int32_t dev_status;
    int32_t s_status;
    int32_t z_status;

    // switch (this->active_device) {
    // case CONTROLLER:
    //     dev_status = this->controller.Process_Input();
    //     s_status = this->controller.driver_wish.SerializeToString(&driver_wish) - 1; //Normalized to 0
    // case KEYBOARD:
    //     dev_status = this->keyboard.Process_Input();
    //     s_status = this->keyboard.driver_wish.SerializeToString(&driver_wish) - 1; //Normalized to 0
    // default:
    //     s_status = -1;
    //     dev_status = -1;
    // }

    dev_status = this->controller.Process_Input();
    s_status = this->controller.driver_wish.SerializeToString(&driver_wish) - 1;
    z_status = this->bus.Publish_Driver_Wish("CONTROLLER", driver_wish);
    usleep(10000);
    return s_status + z_status + dev_status;
}

int32_t ControlCenter::Deinit()
{
    return this->bus.Deinit();
}