#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <iostream>
#include "VideoPipeline.h"
#include "Keyboard.h"
#include "Controller.h"
#include "Device.h"

class Subscriber {

public:
    Subscriber();
    ~Subscriber();

    int32_t Subscribe_To_Video();
    int32_t Unsubscribe_From_Video();
    int32_t Subscribe_To_Device();
    int32_t Unsubscribe_From_Device();


protected:
    VideoSubscriber video_subscriber;
    std::thread video_thread;
    Controller controller;
    Keyboard keyboard;
};

#endif //SUBSCRIBER_H