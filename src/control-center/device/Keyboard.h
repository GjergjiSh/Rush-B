#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Device.h"

#define PRESSED ((ev[i].value == 1 || ev[i].value == 2))
#define VAL 0.1

class Keyboard : public Device {
public:
    Keyboard();
    ~Keyboard() = default;
    int32_t Initialize_Device(const char* device_path) override;
    int32_t Process_Input() override;
    void Print_Driver_Wish() override;

private:
    struct input_event ev[64];
};

#endif /* KEYBOARD_H */
