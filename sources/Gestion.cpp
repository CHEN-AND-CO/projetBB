#include "Gestion.hpp"

Gestion::Gestion(): r{GPIO_RED}, v{GPIO_GREEN}, b{GPIO_BLUE}, bp{GPIO_BP, GPIO::IN}, pwm{GPIO_QAM, GPIO::IN}, an{AN_POTAR} {
    etat_tube_fluo = new char[3];

    etat_tube_fluo[0] = 0;
    etat_tube_fluo[1] = 0;
    etat_tube_fluo[2] = 0;
}

void Gestion::selection(){
  char tube_fluo;
  int ValeurPotentiometre=an.read();  

  if(ValeurPotentiometre<=600){
    tube_fluo='R';
    r.set(1);
    v.set(0);
    b.set(0);
  }else if(ValeurPotentiometre<=1200){
    tube_fluo='V';
    r.set(0);
    v.set(1);
    b.set(0);
  }else{
    tube_fluo='B';
    r.set(0);
    v.set(0);
    b.set(1);
  }
  if(!bp.get()){
    commande_radio(tube_fluo,etat_tube_fluo);
    while(!bp.get());
  }
}

void Gestion::commande_radio(char tube_fluo, char *etat_tube_fluo){
    std::string couleur, status;

    switch(tube_fluo){
        case 'R':
            etat_tube_fluo[0] = !etat_tube_fluo[0];

            if(etat_tube_fluo[0]){
                status="allumé";
            }else{
                status="éteint";
            }
            couleur="rouge";
            
            break;
            case 'V':
                etat_tube_fluo[1] = !etat_tube_fluo[1];

                if(etat_tube_fluo[1]){
                    status="allumé";
                }else{
                    status="éteint";
                }
                couleur="vert";
                
                break;
            case 'B':
                etat_tube_fluo[2] = !etat_tube_fluo[2];

                if(etat_tube_fluo[2]){
                    status="allumé";
                }else{
                    status="éteint";
                }
                couleur="bleu";
                
                break;
    }

    std::cout << "Le tube fluorescent " << couleur << " est " << status << "\n";
}

 void Gestion::GPIO_1to0(int delai1, int delai0){
     
 }