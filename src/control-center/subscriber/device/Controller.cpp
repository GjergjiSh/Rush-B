#include "Controller.h"

using namespace std;

Controller::Controller() { }
Controller::~Controller() { }

/*********************************************************************
 * @brief  Initializes the Controller
 * @return int32_t 0 if successful or -1 if not successful
 *****************************************************************/
int32_t Controller::Initialize_Device()
{
    char name[256] = "Unknown";
    if ((file_descriptor = open(device_path, O_RDONLY)) < 0) {
        fprintf(stderr, "[E] [ Control-Center -> Controller ] Cannot open %s: %s.\n", device_path, strerror(errno));
        return -1;
    } else {
        printf("[I] [ Control-Center -> Controller ] Device Recognized\n");
        ioctl(file_descriptor, JSIOCGNAME(sizeof(name)), name);
        printf("[I] [ Control-Center -> Controller ] Device name: %s\n", name);
    }
    return 0;
}

/********************************************************************
     * @brief Checks if the device is Connected
     * @return TRUE if the Device is Connected and FALSE if it is not
     ****************************************************************/
bool Controller::Connected()
{
    js_event* ev = &event;
    ssize_t bytes;
    bytes = read(file_descriptor, ev, sizeof(*ev));
    if (bytes == sizeof(*ev)) {
        return true;
    }
    return false;
}

/*********************************************************************
     * @brief Updates the coordinates of the thumbstick that is moved
     * @return The moved thumbstick
     *****************************************************************/
size_t Controller::Moved_Stick()
{
    js_event* ev = &event;
    size_t thumbstick = ev->number / 2;

    if (ev->number % 2 == 0)
        stick_coordinates[thumbstick].x = ev->value;
    else
        stick_coordinates[thumbstick].y = ev->value;

    return thumbstick;
}

/*********************************************************************
     * @brief Update DriverWish actions; Engine on/off, Gearshifts
     ****************************************************************/
void Controller::Handle_Button_Events()
{
    js_event* ev = &event;

    if (ev->number == L1) {
        //Move camera left
    }
    else if (ev->number == R1) {
        //Move camera right
    }
}

/***************************************************************************
     * @brief Updates the Acceleration, Brake and Steering values
     * @note: The Linux/Joystick API is somewhat counter-intuitive. Positive
     *        coordinates traslate to downwards movement and vice-versa.
     ***********************************************************************/
void Controller::Handle_Thumbstick_Events()
{
    size_t thumb_stick = Moved_Stick();

    if (thumb_stick == RIGHTSTICK) {

        if (stick_coordinates[RIGHTSTICK].x > 0) // Right Thumbstick Moving Down
        {
            //Slow right servo down
        } else if (stick_coordinates[RIGHTSTICK].x < 0) // Right Thumbstick Moving Up
        {
            //Speed right servo up
        } else // Left Thumbstick not moving
        {
            //Stop right servo
        }
    } else if (thumb_stick == LEFTSTICK) {
        if (stick_coordinates[LEFTSTICK].x > 0) // Left Thumbstick Moving Down
        {
            //Speed left servo up
        } else if (stick_coordinates[LEFTSTICK].x < 0) // Left Thumbstick Moving Up
        {
            //Slow left servo down
        } else // Left Thumbstick not moving
        {
            //Stop left servo
        }
    }
}

/********************************************************************************************
     * @brief Listens for events and processes them as long as the Device is connected
     ****************************************************************************************/
void Controller::Process_Input()
{
    while (Connected()) {
        std::lock_guard<std::mutex> lock(mutex);
        switch (event.type) {
        case JS_EVENT_BUTTON:
            Handle_Button_Events();
            break;
        case JS_EVENT_AXIS:
            Handle_Thumbstick_Events();
            break;
        default:
            break;
        }
        usleep(sleep_timer);
    }
}

void Controller::Start_Thread()
{
    input_thread = thread(&Controller::Process_Input, this);
    std::cout << "[I] [ Control-Center  -> Controller ] Controller Thread Started" << std::endl;
}
