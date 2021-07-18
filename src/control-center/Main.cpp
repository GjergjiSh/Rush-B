#include "ControlCenter.h"
#include "SigHandler.h"

int main(int argc, char* argv[])
{
    //Entry (Init Devices, VideoPipelines and ZMQ Connection)
    ControlCenter* control_center = new ControlCenter();

    //Setting up Signal Handler
    struct sigaction action;
    action.sa_handler = Signal_Handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    if (control_center->Init() == 0) {
        //Controlling Rush-B
        while (RUNNING) {
            if (control_center->Control_Robot() == 0) {
               // control_center->controller.Print_Driver_Wish();
            }
        }
    }

    //Exit
    control_center->Deinit();
    google::protobuf::ShutdownProtobufLibrary();
    exit(0);
}