#include "RushB.h"
#include "SigHandler.h"

int main(int argc, char* argv[])
{
    //Entry (ArduinoLink, VideoPipeline and ZMQ Connection)
    std::unique_ptr<RushB> rush_b = std::make_unique<RushB>("./config.xml");

    if (rush_b->Init() == 0) {
        //Controlling Robot movement
        while (!s_interrupted) {
            Catch_Signals();
            if (rush_b->Control_Robot() != 0)
                break;
        }
    }
    //Exit
    rush_b->Deinit();
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
