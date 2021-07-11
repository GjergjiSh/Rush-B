#ifndef RUSHB_H
#define RUSHB_H

#include "RSubscriber.h"
#include "RPublisher.h"
#include "ArduinoLink.h"

class RushB {

public:
    RushB();
    ~RushB();

    int32_t Init();
    int32_t Deinit();
    int32_t Control_Robot();

    Subscriber* subscriber;
    //Publisher* publisher;
    //ArduinoLink* arduino_link;
};

#endif //RUSHB_H