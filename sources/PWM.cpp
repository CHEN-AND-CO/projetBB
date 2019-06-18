#include "PWM.hpp"

void PWM::on(){
    if(counter < limit){
        set(true);
    }else{
        set(false);
    }

    counter++;
    counter%=10;
}