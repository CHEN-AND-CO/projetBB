#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <ctime>
#include "GPIO.hpp"

#define usleep(x) std::this_thread::sleep_for(std::chrono::microseconds(x))

#define GPIO_RED    1 * 32 + 18
#define GPIO_GREEN  1 * 32 + 28
#define GPIO_BLUE   3
#define GPIO_QAM    1 * 32 + 19

#define UP_TIME      333
#define DOWN_TIME    666

void hInterrupt(int sig) {
    std::cout << "SIGINT (Ctrl+C) caught, exiting...\n";

    exit(sig);
}

int main(){
    //Setting interrupt handler
    signal(SIGINT, hInterrupt);
    
    GPIO pwm{GPIO_QAM};

    while(true){
        pwm.set(true);
        usleep(UP_TIME);
        pwm.set(false);
        usleep(DOWN_TIME);
    }

    return 0;
}