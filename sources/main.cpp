#include <future>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <termio.h>

#include "Gestion.hpp"

void set_mode(int want_key)
{
	static struct termios old, newT;
	if (!want_key) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		return;
	}
 
	tcgetattr(STDIN_FILENO, &old);
	newT = old;
	newT.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newT);
}
 
int get_key()
{
	int c = 0;
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;
 
	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
	select(STDIN_FILENO + 1, &fs, 0, 0, &tv);
 
	if (FD_ISSET(STDIN_FILENO, &fs)) {
		c = getchar();
		set_mode(0);
	}
	return c;
}

int GetLineFromCin() {
  set_mode(1);
	while (!get_key());
  //set_mode(0);
  
  return 1;
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

      while(true){
          if(future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
            auto line = future.get();

            std::cout << "Choisissez un mode de fonctionnement :" << "\n";
            std::cout << "\t" << "0) Continuer en mode autonome" << "\n";
            std::cout << "\t" << "1) Mode recherche de prise" << "\n";
            std::cout << "\t" << "2) Mode menu" << "\n";

            int choix;
            std::cin >> choix;

            switch(choix){
              case 1:
                std::cout << "Vous avez choisi le mode recherche de prise !" << "\n";
                int debut, longueur, activ, limit; 

                std::cout << "Debut : ";
                std::cin >> debut;
                std::cout << "Longueur : ";
                std::cin >> longueur;
                std::cout << "Etat : ";
                std::cin >> activ;
                std::cout << "Limit : ";
                std::cin >> limit;
                gestion.recherche(debut, longueur, activ, limit);

                exit(EXIT_SUCCESS);
                break;
              case 2:
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
                };

                exit(EXIT_SUCCESS);
                break;
              case 0:
              default:
                break;
            }
            
            future = std::async(std::launch::async, GetLineFromCin);
          }
        
        gestion.selection();
      }
    break;
  }

  return EXIT_SUCCESS;
}