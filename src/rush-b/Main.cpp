#include "RushB.h"
#include "SigHandler.h"

int main(int argc, char* argv[])
{
    //Entry (ArduinoLink, VideoPipeline and ZMQ Connection)
    RushB* rush_b = new RushB();

    if (rush_b->Init() == 0) {
        //Controlling Robot movement
        while (!s_interrupted) {
	    s_catch_signals();
            int32_t status = rush_b->Control_Robot();
            if (status != 0) break;
        }
    }
    //Exit
    rush_b->Deinit();
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
