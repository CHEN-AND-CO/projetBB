#ifndef PWM_HPP
#define PWM_HPP

#include <iostream>
#include <fstream>

#define DEVICE_MANAGER_PATH "/sys/devices/bone_capemgr.9"
#define PWM_PATH "/sys/devices/ocp.3/pwm_test_P9_16.15"

class PWM {
    public:
    PWM(int period = 1800, int polarity = 0);

    void setPeriod(int period);
    void setPolarity(int polarity);
    void setRun(bool run);
    void setDuty(int duty);

    void mod(unsigned int duty);
    private:

};

#endif /* PWM_HPP */