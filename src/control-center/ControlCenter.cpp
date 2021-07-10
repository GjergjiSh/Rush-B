#include "ControlCenter.h"

ControlCenter::ControlCenter() { }
ControlCenter::~ControlCenter() { }

int32_t ControlCenter::Connect_Device()
{
    if (this->active_device == "KEYBOARD") {
        if (this->keyboard.Initialize_Device() == 0) {
            this->keyboard.Start_Thread();
            return 0;
        }
    } else if (this->active_device == "CONTROLLER") {
        if (this->controller.Initialize_Device() == 0) {
            this->controller.Start_Thread();
            return 0;
        }
    } else {
        std::cerr << "[E] [ Control-Center -> Connect Device ] Unaccepted parameter for the active device: "
                  << this->active_device << std::endl;
    }
    return -1;
}

int32_t ControlCenter::Disconnect_Device()
{
    if (this->active_device == "KEYBOARD") {
        if (this->keyboard.input_thread.joinable()) {
            this->keyboard.input_thread.join();
            return 0;
        }
    } else if (this->active_device == "CONTROLLER") {
        if (this->controller.input_thread.joinable()) {
            this->controller.input_thread.join();
            return 0;
        }
    }
    return -1;
}

int32_t ControlCenter::Init()
{
    this->subscriber = new Subscriber();
    this->publisher = new Publisher();

    { //TODO: The code in this scope temporarily hardcoded. these items should be configurable through the control-center.cfg file
        this->controller.device_path = "/dev/input/by-id/usb-Inno_GamePad.._Inno_GamePad.._0000001-joystick";
        this->active_device = "CONTROLLER";
        this->publisher->zqm_pub_transport = "127.0.0.1:5001";
        this->subscriber->video_subscriber.port = 5000;
        this->controller.sleep_timer = 1000;
    }

    int32_t init_zmq_status = this->publisher->ZMQ_Init_Connection();
    int32_t sub_video_status = this->subscriber->Subscribe_To_Video();
    int32_t device_status = this->Connect_Device();

    if (init_zmq_status + device_status + sub_video_status == 0) {
        std::cout << "[I] [ Control-Center -> Init ] Control-Center Successfuly Initialized " << std::endl;
        return 0;
    } else {
        std::cerr << "[E] [ Control-Center -> Init ] Control-Center Failed to Initialize " << std::endl;
    }
    return -1;
}

int32_t ControlCenter::Deinit()
{

    int32_t deinit_zmq_status = this->publisher->ZMQ_Deinit_Connection();
    int32_t unsub_device_status = this->subscriber->Unsubscribe_From_Video();
    int32_t device_status = this->Disconnect_Device(); //TODO: Currently failing to exit cleanly here

    if (deinit_zmq_status + unsub_device_status + device_status == 0) {
        std::cout << "[I] [ Control-Center -> Deinit ] Control-Center Successfuly Deintialized " << std::endl;
        return 0;
    } else {
        std::cerr << "[E] [ Control-Center -> Deinit ] Control-Center Failed to Deintialize " << std::endl;
    }

    delete this->subscriber;
    delete this->publisher;
    return -1;
}

int32_t ControlCenter::Control_Robot()
{
    std::string driver_wish;
    int32_t s_status;

    std::lock_guard<std::mutex> lock(mutex);
    if (this->active_device == "CONTROLLER") {
        s_status = this->controller.driver_wish.SerializeToString(&driver_wish);
    } else if (this->active_device == "KEYBOARD") {
        s_status = this->keyboard.driver_wish.SerializeToString(&driver_wish);
    } else {
        s_status = -1;
    }

    int32_t z_status = this->publisher->ZMQ_Send("CONTROLLER", driver_wish);

    return s_status + z_status;
}