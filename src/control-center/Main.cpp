#include "ControlCenter.h"

int main()
{
    ControlCenter* control_center = new ControlCenter();
    control_center->Init();
    control_center->Deinit();
    delete control_center;
    return 0;
}