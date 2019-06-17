#ifndef GESTION_HPP
#define GESTION_HPP

#include <memory>
#include <vector>

#include "defines.hpp"
#include "GPIO.hpp"
#include "ADC.hpp"

class Gestion {
    public:
    Gestion(): r{GPIO_RED}, v{GPIO_GREEN}, b{GPIO_BLUE}, bp{GPIO_BP, GPIO::IN}, an{AN_POTAR} {}

    void selection();
    void commande_radio(char tube_fluo, std::vector<char> &etat_tube_fluo);
    private:
    GPIO r,v,b;
    GPIO bp;
    ADC an;
    std::vector<char> etat_tube_fluo;
};

#endif /* GESTION_HPP */
