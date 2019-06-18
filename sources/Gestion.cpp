#include "Gestion.hpp"

Gestion::Gestion(): r{GPIO_RED}, v{GPIO_GREEN}, b{GPIO_BLUE}, bp{GPIO_BP, GPIO::IN}, pwm{GPIO_QAM, 4*TREF}, an{AN_POTAR} {
    etat_tube_fluo = new char[3];

    etat_tube_fluo[0] = 0;
    etat_tube_fluo[1] = 0;
    etat_tube_fluo[2] = 0;
}

void Gestion::selection(){
  char tube_fluo;
  auto valeurPotentiometre=an.read();

  if(valeurPotentiometre<=600){
    tube_fluo='R';
    r.set(true);
    v.set(false);
    b.set(false);
  }else if(valeurPotentiometre<=1200){
    tube_fluo='V';
    r.set(false);
    v.set(true);
    b.set(false);
  }else{
    tube_fluo='B';
    r.set(false);
    v.set(false);
    b.set(true);
  }

  if(!bp.get()){
    commande_radio(tube_fluo,etat_tube_fluo);
    while(!bp.get()); // Attente de relachement du bouton poussoir
  }
}

void Gestion::commande_radio(char tube_fluo, char *etat_tube_fluo){
    std::string couleur, status;
    int i=-1;

    switch(tube_fluo){
        case 'R':
            i = 0;
            couleur="rouge";
        break;
        case 'V':
            i = 3;
            couleur="vert";
            break;
        case 'B':
            i = 2;
            couleur="bleu";
            break;
        default:
            return;
        break;
    }

    etat_tube_fluo[i] = !etat_tube_fluo[i];

    if(etat_tube_fluo[i]){
        status="allumé";
    }else{
        status="éteint";
    }

    std::cout << "Le tube fluorescent " << couleur << " est " << status << "\n";
}

 void Gestion::GPIO_1to0(int delai1, int delai0){
    std::cout << "OK" << "\n";
     pwm.set(true);
     //delai1-=TREF_COR;
     usleep(delai1);
     pwm.set(false);
     //delai0-=TREF_COR;
     usleep(delai0);
 }
