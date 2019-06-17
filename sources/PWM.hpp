#ifndef PWM_HPP
#define PWM_HPP

#include <chrono>
#include <thread>
#include <queue>

#include "GPIO.hpp"

#define usleep(x) std::this_thread::sleep_for(std::chrono::microseconds(x))

class PWM : public GPIO {
    #define T1_T3(tHigh)  set(true);usleep(tHigh);set(false);usleep(tHigh*3);
    #define T3_T1(tHigh)  set(true);usleep(tHigh*3);set(false);usleep(tHigh);

    public:
    PWM(int port, unsigned int period, unsigned int tHigh = 0):
        GPIO(port),
        period{period},
        dutyCycle{0},
        tHigh{tHigh}
    {}

    unsigned int getPeriod() const& { return period; }
    unsigned int getTHigh() const& { return tHigh; }
    float getDutyCycle() const& { return dutyCycle; }
    void setPeriod(const unsigned int &_period){ period = _period; }
    void setTHigh(const unsigned int &_tHigh){ tHigh = _tHigh; }
    void setDutyCycle(const float &dutyRate);
    void setT(const unsigned int &_tHigh);

    void run();
    private:
    unsigned int period;
    float dutyCycle;
    unsigned int tHigh;
    std::queue<char> buffer;
};

#endif /* PWM_HPP */