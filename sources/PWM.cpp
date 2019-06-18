#include "PWM.hpp"

void PWM::setDutyCycle(const float &dutyRate){
    dutyCycle = dutyRate;
    tHigh = period*dutyCycle;
}

void PWM::setT(const unsigned int &_tHigh){
    tHigh = _tHigh;
    dutyCycle = (float) tHigh / period;
}

void PWM::start(){
    // std::thread thread([this](){
    //         while(true){
    //             mutex.lock();
    //             run();
    //             usleep(100);
    //             mutex.unlock();
    //         }
    //     }
    // );
}

void PWM::run(){
    if(!buffer.size()){
        set(false);
        usleep(period);
    }else{
        switch(buffer.front()){
            case '0':
                T1_T3(tHigh);
                T3_T1(tHigh);
                break;
            case '1':
                T1_T3(tHigh);
                T1_T3(tHigh);
                break;
            case '2':
                T3_T1(tHigh);
                T3_T1(tHigh);
                break;
            default:
                set(false);
                usleep(period);
                break;
        }
        buffer.pop();
    }
}
