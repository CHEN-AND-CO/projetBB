#include "Gestion.hpp"

int main(int argc, char *argv[]){
    Gestion gestion;
    while(true){
      gestion.selection();

      gestion.GPIO_1to0(TREF, 3*TREF);
    }
    return EXIT_SUCCESS;
}
