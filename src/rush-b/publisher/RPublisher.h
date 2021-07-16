#ifndef R_PUBLISHER_H
#define R_PUBLISHER_H

#include "RVideoPipeline.h"
#include "ArduinoLink.h"

class Publisher {

public:
    Publisher();
    ~Publisher();

    int32_t Start_Publishing_Video();
    int32_t Stop_Publishing_Video();

    VideoPublisher video_publisher;
    ArduinoLink arduino_link;
};

#endif /* R_PUBLISHER_H */