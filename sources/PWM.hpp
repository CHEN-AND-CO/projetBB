#ifndef PWM_HPP
#define PWM_HPP

#include <chrono>
#include <thread>
#include <mutex>
#include <queue>

#include "GPIO.hpp"

#define usleep(x) std::this_thread::sleep_for(std::chrono::microseconds(x))

class PWM : public GPIO {
     public:
    PWM(int port, unsigned int dutyCycle = 50):
        GPIO(port),
        dutyCycle{dutyCycle}
    {}

    std::shared_ptr<std::mutex> getMutex() const& { return mutex;}
    unsigned int getDutyCycle() const& { return dutyCycle; }
    void setDutyCycle(const unsigned int &_dutyCycle){ dutyCycle = _dutyCycle; }
    bool set(bool state);

    void run();
    private:
    unsigned int dutyCycle;
    std::shared_ptr<std::mutex> mutex;
};

#endif /* PWM_HPP */