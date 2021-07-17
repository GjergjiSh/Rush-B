#include "Subscriber.h"

Subscriber::Subscriber() {};
Subscriber::~Subscriber() {};

int32_t Subscriber::Subscribe_To_Video()
{
    if (this->video_subscriber.Construct_Pipeline("Control Center Video Pipeline", &this->video_subscriber.pipeline) == 0) {
        int32_t pipeline_status = this->video_subscriber.Set_Pipeline_State_Playing();
        if (pipeline_status == 0) this->video_thread = std::thread(&VideoSubscriber::Start_Gloop, this->video_subscriber);
        return pipeline_status;
    }
    return -1;
}

int32_t Subscriber::Unsubscribe_From_Video()
{
    int32_t status = 0;
    this->video_thread.detach();
    status = this->video_subscriber.Destroy_Pipeline();
    return status;
}

