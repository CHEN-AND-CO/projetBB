#include "Gestion.hpp"

int main(int argc, char *argv[]){
    switch(argc){
      default:
        for(auto i = 0; i < argc; i++){
          std::cout << argv[i] << "\t";
        }
        std::cout << "\n";
        break;
    }

    Gestion gestion;
    while(true){
      gestion.selection();

      gestion.GPIO_1to0(TREF, 3*TREF);
    }
    return EXIT_SUCCESS;
}
