#include "RushB.h"
#include "SigHandler.h"
#include "unistd.h"

int main(int argc, char* argv[])
{

    //Setting up Signal Handler
    struct sigaction action;
    action.sa_handler = Signal_Handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    //Entry (ArduinoLink, VideoPipeline and ZMQ Connection)
    RushB* rush_b = new RushB();

    if (rush_b->Init() == 0) {

        //Controlling Robot movement
        while (RUNNING) {
            int32_t status = rush_b->Control_Robot();
            usleep(1000);
            if (status != 0) break;
        }
    }

    //Exit
    rush_b->Deinit();
    return 0;
}