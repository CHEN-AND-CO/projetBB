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

void Gestion::commande_radio(char tube_fluo, std::vector<char> &etat_tube_fluo){

}
