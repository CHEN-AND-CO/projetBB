#include "PWM.hpp"

void PWM::setT(const unsigned int &_tHigh, const unsigned int &_tLow){
    tHigh = _tHigh;
    tLow  = _tLow;
}

void PWM::run(){
    if(!buffer.size()){
        set(false);
        usleep(period);
    }else{
        switch(buffer.front()){
            case '0':
                T1_T3(tHigh, tLow);
                T3_T1(tHigh, tLow);
                break;
            case '1':
                T1_T3(tHigh, tLow);
                T1_T3(tHigh, tLow);
                break;
            case '2':
                T3_T1(tHigh, tLow);
                T3_T1(tHigh, tLow);
                break;
            case 'S':
                T1_T32(tHigh, tLow);
            break;
            default:
                set(false);
                usleep(period);
                break;
        }
        buffer.pop();
    }
}
