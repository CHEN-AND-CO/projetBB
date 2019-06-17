#include "Gestion.hpp"

Gestion::Gestion(): r{GPIO_RED}, v{GPIO_GREEN}, b{GPIO_BLUE}, bp{GPIO_BP, GPIO::IN}, an{AN_POTAR} {
    etat_tube_fluo.push_back(0); //R
    etat_tube_fluo.push_back(0); //V
    etat_tube_fluo.push_back(0); //B
}

void Gestion::selection(){
  char tube_fluo;
  int ValeurPotentiometre=this->an.read();
  std::cout << ValeurPotentiometre<<"\n";
  if(ValeurPotentiometre<=600){
    tube_fluo='R';
    this->r.set(1);
    this->v.set(0);
    this->b.set(0);
  }else if(ValeurPotentiometre<=1200){
    tube_fluo='V';
    this->r.set(0);
    this->v.set(1);
    this->b.set(0);
  }else{
    tube_fluo='B';
    this->r.set(0);
    this->v.set(0);
    this->b.set(1);
  }
  if(this->bp.get()){
    commande_radio(tube_fluo,etat_tube_fluo);
  }
}

void Gestion::commande_radio(char tube_fluo, std::vector<bool> &etat_tube_fluo){
    std::string couleur, status;

    switch(tube_fluo){
        case 'R':
            etat_tube_fluo[0] != etat_tube_fluo[0];

            if(etat_tube_fluo[0]){
                status="allumé";
            }else{
                status="éteint";
            }
            couleur="rouge";
            
            break;
            case 'v':
                etat_tube_fluo[1] != etat_tube_fluo[1];

                if(etat_tube_fluo[1]){
                    status="allumé";
                }else{
                    status="éteint";
                }
                couleur="vert";
                
                break;
            case 'B':
                etat_tube_fluo[2] != etat_tube_fluo[2];

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
