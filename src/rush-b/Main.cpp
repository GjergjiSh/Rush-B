#include "RushB.h"
#include "SigHandler.h"

int main(int argc, char* argv[])
{
    DRAW_LINE //Entry (ArduinoLink, VideoPipeline and ZMQ Connection)
    RushB* rush_b = new RushB();

    //Setting up Signal Handler
    struct sigaction action;
    action.sa_handler = Signal_Handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    if (rush_b->Init() == 0) {
        //Controlling Robot movement
        while (RUNNING) {

            int32_t status = rush_b->Control_Robot();
            if (status != 0) break;
        }
    }
    //Exit
    rush_b->Deinit();
    google::protobuf::ShutdownProtobufLibrary();
    exit(0);
}