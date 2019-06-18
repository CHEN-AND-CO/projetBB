#ifndef PWM_HPP
#define PWM_HPP

#include "GPIO.hpp"

class PWM : public GPIO {
    public:
    PWM(int port): GPIO(port), limit{0}, counter{0} {}

    void on();
    void off(){ set(false); }

    void setLimit(const int &_limit){ limit = _limit; }
    int getLimit() const& { return limit; }
    private:
    int limit;
    int counter;
};

#endif /* PWM_HPP */