#ifndef GESTION_HPP
#define GESTION_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>

#include "defines.hpp"
#include "GPIO.hpp"
#include "ADC.hpp"


#define PWM_T1_T3(tHigh, tLow)  GPIO_1to0(tHigh, 3*tLow);
#define PWM_T3_T1(tHigh, tLow)  GPIO_1to0(3*tHigh, tLow);
#define PWM_T1_T32(tHigh, tLow) GPIO_1to0(tHigh, 32*tLow);

class Gestion {
    public:
    Gestion();
    ~Gestion(){ delete etat_tube_fluo; }

    void selection();
    void commande_radio(char tube_fluo, char *etat_tube_fluo);
    void GPIO_1to0(int delai1, int delai0);
    void trans_data_433MHz(char data);
    void trans_trame_433MHz(char maison, char objet, char activation, char repetition);

    private:
    GPIO r,v,b;
    GPIO bp;
    GPIO pwm;
    ADC an;
    char *etat_tube_fluo;
    std::vector<std::string> trit;
};

#endif /* GESTION_HPP */
