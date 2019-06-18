#ifndef GESTION_HPP
#define GESTION_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>

#include "defines.hpp"
#include "GPIO.hpp"
#include "ADC.hpp"
#include "PWM.hpp"

class Gestion {
    public:
    Gestion();
    ~Gestion(){ delete etat_tube_fluo; }

    void selection();
    void commande_radio(char tube_fluo, char *etat_tube_fluo);
    void GPIO_1to0(int delai1, int delai0);
    void trans_data_433MHz(char data);

    PWM getPwm() const& { return pwm; }
    private:
    GPIO r,v,b;
    GPIO bp;
    PWM pwm;
    ADC an;
    char *etat_tube_fluo;
};

#endif /* GESTION_HPP */
