#include "PWM.hpp"

PWM::PWM(int period, int polarity){
    std::ofstream out{ DEVICE_MANAGER_PATH "/slots"};

    out << "am33xx_pwm";
    out.flush();

    out << "bone_pwm_P9_14";
    out.flush();

    setPeriod(period);
    setPolarity(polarity);
}

void PWM::setPeriod(int period){
    std::ofstream out{ PWM_PATH "/period"};

    out << period;
    out.flush();
}

void PWM::setPolarity(int polarity){
    std::ofstream out{ PWM_PATH "/polarity"};

    out << polarity;
    out.flush();
}

void PWM::setRun(bool run){
    std::ofstream out{ PWM_PATH "/run"};

    out << ((run)?1:0);
    out.flush();
}

void PWM::setDuty(int duty){
    std::ofstream out{ PWM_PATH "/duty"};

    out << duty;
    out.flush();
}

void PWM::mod(unsigned int duty){
    setRun(false);
    setDuty(duty);
    setRun(true);
}