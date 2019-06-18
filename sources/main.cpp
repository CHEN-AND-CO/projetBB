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
    std::string chaine="10S";
    while(true){
      //gestion.selection();
      for(const auto &charac: chaine){
        trans_data_433MHz(charac);
      }
      //gestion.GPIO_1to0(TREF-TREF_CORH, 3*(TREF-TREF_CORL));
      //gestion.getPwm().run();
    }
    return EXIT_SUCCESS;
}
