#include <future>
#include "Gestion.hpp"

std::string GetLineFromCin() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int main(int argc, char *argv[]){
  Gestion gestion;

  switch(argc){
    case 5:
      std::cout << "maison=" << *argv[1] 
                << "\t objet=" << std::atoi(argv[2])
                << "\t activation=" << std::atoi(argv[3])
                << "\t repetitions=" << std::atoi(argv[4])
                << "\n";
      gestion.trans_trame2_433MHz(
        *argv[1],
        std::atoi(argv[2]),
        !std::atoi(argv[3]),
        std::atoi(argv[4])
      );
      break;
    default:
      auto future = std::async(std::launch::async, GetLineFromCin);
      bool menuPrincipal = true, menuChoix=false;

      while(true){
        if (future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
          auto line = future.get();
          future = std::async(std::launch::async, GetLineFromCin);

          if(menuPrincipal){
            std::cout << "Choisissez un mode de fonctionnement :" << "\n";
            std::cout << "\t" << "0) Continuer en mode autonome" << "\n";
            std::cout << "\t" << "1) Mode recherche de prise" << "\n";
            std::cout << "\t" << "2) Mode menu" << "\n";

            int choix;
            std::cin >> choix;

            switch(choix){
              case 1:
                std::cout << "Vous avez choisi le mode recherche de prise !" << "\n";
                int debut, longueur, etat, limit; 

                std::cout << "Debut : ";
                std::cin >> debut;
                std::cout << "Longueur : ";
                std::cin >> longueur;
                std::cout << "Etat : ";
                std::cin >> etat;
                std::cout << "Limit : ";
                std::cin >> limit;
                gestion.recherche(debut, longueur, etat, limit);

                exit(EXIT_SUCCESS);
                break;
              case 2:
                menuPrincipal=false;
                menuChoix=true;
                break;
              case 0:
              default:
                break;
            }
          }else if(menuChoix){
            int etat; char couleur;

            std::cout << "Vous avez le mode menu !" << "\n";
            std::cout << "Eteindre ou Allumer ? (0/1) : ";
            std::cin >> etat;
            std::cout << "Couleur tube ? (R/V/B) ou T (tous) : ";
            std::cin >> couleur;
                
            if(std::toupper(couleur) == 'T'){
              gestion.commande_radio_manuelle('R', etat);
              gestion.commande_radio_manuelle('V', etat);
              gestion.commande_radio_manuelle('B', etat);
            }else{
              gestion.commande_radio_manuelle(std::toupper(couleur), etat);
            }

            menuChoix = false;
          }
        }else{
          menuChoix = true;
        }
        
        gestion.selection();
      }
      break;
  }

  return EXIT_SUCCESS;
}