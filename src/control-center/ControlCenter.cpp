#include "ControlCenter.h"

ControlCenter::ControlCenter(){}
ControlCenter::~ControlCenter(){}

int32_t ControlCenter::Init()
{
    this->subscriber = new Subscriber();
    this->publisher = new Publisher();

    //TODO: This needs to be read from the control center cfg file
    this->publisher->zqm_pub_transport = "127.0.0.1:5001";

    int32_t init_zmq_status = this->publisher->ZMQ_Init_Connection();
    int32_t sub_device_status = this->subscriber->Subscribe_To_Device();
    int32_t sub_video_status = this->subscriber->Subscribe_To_Video();

    if (init_zmq_status + sub_device_status + sub_video_status == 0) {
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
    int32_t unsub_video_status = this->subscriber->Unsubscribe_From_Device(); //ISSUE: Currently Failing to exit cleanly here

    if (deinit_zmq_status + unsub_device_status + unsub_video_status == 0) {
        std::cout << "[I] [ Control-Center -> Deinit ] Control-Center Successfuly Deintialized " << std::endl;
        return 0;
    } else {
        std::cerr << "[E] [ Control-Center -> Deinit ] Control-Center Failed to Deintialize " << std::endl;
    }

    delete this->subscriber;
    delete this->publisher;
    return -1;
}


int main()
{
    ControlCenter *control_center = new ControlCenter();
    control_center->Init();
    control_center->Deinit();

}