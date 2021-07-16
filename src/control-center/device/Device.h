#ifndef DEVICE_H
#define DEVICE_H

#include "PBDriverWish.pb.h"
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <linux/joystick.h>
#include <mutex>
#include <string.h>
#include <thread>
#include <unistd.h>

class Device {
public:
    virtual ~Device() = default;
    virtual int32_t Process_Input() = 0;
    virtual int32_t Initialize_Device() = 0;
    virtual void Print_Driver_Wish() = 0;

    const char* device_path;
    int32_t file_descriptor;

    PBDriverWish::PBDriverWish driver_wish;

};
#endif /* DEVICE_H */
