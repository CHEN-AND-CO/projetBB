#ifndef PWM_HPP
#define PWM_HPP

#include <chrono>
#include <thread>
#include <queue>

#include "GPIO.hpp"

#define usleep(x) std::this_thread::sleep_for(std::chrono::microseconds(x))

class PWM : public GPIO {
    #define T1_T3(tHigh, tLow)  set(true);usleep(tHigh);set(false);usleep(tLow*3);
    #define T3_T1(tHigh, tLow)  set(true);usleep(tHigh*3);set(false);usleep(tLow);
    #define T1_T32(tHigh, tLow) set(true);usleep(tHigh);set(false);usleep(tLow*32);

    public:
    PWM(int port, unsigned int period, unsigned int tHigh = 0, unsigned int tLow = 0):
        GPIO(port),
        period{period},
        tHigh{tHigh},
        tLow{tLow}
    {}

    PWM& operator+=(const std::string &s){ for(const auto &i : s) buffer.push(i); return *this; }
    PWM& operator+=(const char *s){ while(*s) buffer.push(*(s++)); return *this; }
    PWM& operator+=(const char &c){ buffer.push(c); return *this; }

    unsigned int getPeriod() const& { return period; }
    unsigned int getTHigh() const& { return tHigh; }
    unsigned int getTLow() const& { return tLow; }
    void setPeriod(const unsigned int &_period){ period = _period; }
    void setTHigh(const unsigned int &_tHigh){ tHigh = _tHigh; }
    void setTLow(const unsigned int &_tLow){ tLow = _tLow; }
    void setT(const unsigned int &_tHigh, const unsigned int &_tLow);

    void run();
    private:
    unsigned int period;
    unsigned int tHigh, tLow;
    std::queue<char> buffer;
};

#endif /* PWM_HPP */