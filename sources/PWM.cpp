#include "PWM.hpp"

void PWM::run(){
    mutex->lock();
    set(true);
    usleep(dutyCycle);
    set(false);
    usleep(100-dutyCycle);
    mutex->unlock();
}

bool PWM::set(bool state){
    std::ofstream out{ GPIO_PATH "/gpio" + std::to_string(port) + "/value" };

    if(!out.bad()){
        out << ((state)?1:0);
        out.flush();

        return true;
    }

    return false;
}
