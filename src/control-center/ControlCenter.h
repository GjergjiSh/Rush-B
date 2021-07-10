#include "Subscriber.h"
#include "Publisher.h"
#include "Keyboard.h"
#include "Controller.h"

class ControlCenter {

public:
    ControlCenter();
    ~ControlCenter();

    int32_t Connect_Device();
    int32_t Disconnect_Device();

    int32_t Init();
    int32_t Deinit();

    std::string active_device;

    Subscriber* subscriber;
    Publisher* publisher;
    Keyboard keyboard;
    Controller controller;

};