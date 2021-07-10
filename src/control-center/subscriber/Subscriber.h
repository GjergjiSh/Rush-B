#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <iostream>
#include "VideoPipeline.h"
#include <thread>

class Subscriber {

public:
    Subscriber();
    ~Subscriber();

    int32_t Subscribe_To_Video();
    int32_t Unsubscribe_From_Video();

    VideoSubscriber video_subscriber;

protected:
    std::thread video_thread;

};

#endif //SUBSCRIBER_H