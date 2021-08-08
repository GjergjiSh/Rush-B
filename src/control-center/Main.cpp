#include "ControlCenter.h"
#include "SigHandler.h"

int main(int argc, char* argv[])
{
    DRAW_LINE //Entry (Init Devices, VideoPipelines and ZMQ Connection)
    ControlCenter* control_center = new ControlCenter("./config.xml");

    //Setting up Signal Handler
    struct sigaction action;
    action.sa_handler = Signal_Handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

     if (control_center->Init() == 0) {
         //Controlling Rush-B
         while (RUNNING) {
             control_center->Control_Robot();
         }
     }

    //Exit
    control_center->Deinit();
    google::protobuf::ShutdownProtobufLibrary();
    exit(0);
}