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
    void trans_trame2_433MHz(char maison, char objet, char activation, char repetition);
    std::string convertisseur(int decimal=0, int bits=4);
    void commande_radio_manuelle(char tube_fluo, int etat);
    void recherche(int debut, int longueur, int etat, int limit = 8);

    private:
    PWM r,v,b;
    GPIO bp;
    GPIO pwm;
    ADC an;
    char tube_fluo;
    char *etat_tube_fluo;
    std::vector<std::string> trit;
};

#endif /* GESTION_HPP */
