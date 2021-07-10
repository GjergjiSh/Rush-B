#ifndef DEVICE_H
#define DEVICE_H

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
    virtual void Process_Input() = 0;
    virtual void Start_Thread() = 0;
    virtual int32_t Initialize_Device() = 0;

    const char* device_path;
    int32_t file_descriptor;
    std::mutex mutex;
    std::thread input_thread;
    int32_t sleep_timer;
};
#endif /* DEVICE_H */
