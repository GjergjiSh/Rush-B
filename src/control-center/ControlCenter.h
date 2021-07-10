#include "Subscriber.h"
#include "Publisher.h"

class ControlCenter {

public:
    ControlCenter();
    ~ControlCenter();

    int32_t Init();
    int32_t Deinit();

    Subscriber *subscriber;
    Publisher *publisher;

};