#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include "Controller.h"
#include "Keyboard.h"
#include "Publisher.h"
#include "Subscriber.h"

class ControlCenter {

public:
    ControlCenter();
    ~ControlCenter();

    int32_t Connect_Device();

    int32_t Init();
    int32_t Control_Robot();
    int32_t Deinit();

    std::string active_device;

    Subscriber* subscriber;
    Publisher* publisher;
    Keyboard keyboard;
    Controller controller;

};

#endif /* CONTROLCENTER_H */