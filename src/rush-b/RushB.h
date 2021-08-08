#ifndef RUSHB_H
#define RUSHB_H

#define DRAW_LINE                                                                                    \
    std::cout << " ================================================================= " << std::endl; \
    std::cout << " ----------------------------|  Rush B  |------------------------- " << std::endl; \
    std::cout << " ================================================================= " << std::endl;

#include "RBus.h"
#include "RConfigurator.h"

class RushB {

public:
    RushB(const char* config_path);
    ~RushB() = default;

    int32_t Init();
    int32_t Deinit();
    int32_t Control_Robot();

private:
    void Kill_Servos();

    Configurator* configurator;
    Bus bus;
};

#endif //RUSHB_H