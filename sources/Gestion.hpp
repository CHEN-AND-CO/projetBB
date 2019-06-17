#ifndef GESTION_HPP
#define GESTION_HPP

#include <memory>
#include <vector>

#include "GPIO.hpp"

class Gestion {
    public:
    Gestion(){}

    void selection();
    void commande_radio(char tube_fluo, std::vector<char> &etat_tube_fluo);
    private:
};

#endif /* GESTION_HPP */