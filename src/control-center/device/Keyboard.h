#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Device.h"

#define PRESSED ((ev[i].value == 1 || ev[i].value == 2))
#define VAL 0.1

class Keyboard : public Device {
public:
    Keyboard();
    ~Keyboard();
    int32_t Initialize_Device();
    int32_t Process_Input();
    struct input_event ev[64];
    void Print_Driver_Wish();
};

#endif /* KEYBOARD_H */
