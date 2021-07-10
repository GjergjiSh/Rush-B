#include "Subscriber.h"

Subscriber::Subscriber() {};
Subscriber::~Subscriber() {};

int32_t Subscriber::Subscribe_To_Video()
{
    if (this->video_subscriber.Construct_Pipeline("Control Center Video Pipeline", &this->video_subscriber.pipeline) == 0) {
        this->video_thread = std::thread(&VideoSubscriber::Start_Gloop, this->video_subscriber);
        return 0;
    }
    return -1;
}

int32_t Subscriber::Unsubscribe_From_Video()
{
    this->video_subscriber.Destroy_Pipeline();
    this->video_thread.join();
    return 0;
}

int32_t Subscriber::Subscribe_To_Device()
{
    // if { //controller active in cfg
    //     //this->controller.device_path = //read from cfg
    //     if (this->controller.Initialize_Device() == 0) {
    //         this->controller.Start_Thread();
    //         return 0;
    //     }
    // } else if { // keyboard active in cfg
    //     //this->keyboard.device_path = //read from cfg
    //     if (this->keyboard.Initialize_Device() == 0) {
    //         this->keyboard.Start_Thread();
    //         return 0;
    //     }
    // }
    return -1;
}