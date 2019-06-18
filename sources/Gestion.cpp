#include "Gestion.hpp"

Gestion::Gestion(): r{GPIO_RED}, v{GPIO_GREEN}, b{GPIO_BLUE}, bp{GPIO_BP, GPIO::IN}, pwm{GPIO_QAM, 4*TREF}, an{AN_POTAR} {
    etat_tube_fluo = new char[3];

    etat_tube_fluo[0] = 1;
    etat_tube_fluo[1] = 1;
    etat_tube_fluo[2] = 1;

    for(auto i=0; i<256; i++)trit.push_back("");
    trit['A'] = TRIT_A;
    trit['B'] = TRIT_B;
    trit['C'] = TRIT_C;
    trit['D'] = TRIT_D;
    trit[1]   = TRIT_1;
    trit[2]   = TRIT_2;
    trit[3]   = TRIT_3;
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

    auto time = std::chrono::system_clock::now();
    while(!bp.get()){
        if(std::chrono::system_clock::now()-time > std::chrono::seconds(2)){
            etat_tube_fluo[0] = !etat_tube_fluo[0];
            etat_tube_fluo[1] = !etat_tube_fluo[1];
            etat_tube_fluo[2] = !etat_tube_fluo[2];
            trans_trame_433MHz('D', 1, etat_tube_fluo[0], REPETITIONS);
            trans_trame_433MHz('C', 2, etat_tube_fluo[1], REPETITIONS);
            trans_trame_433MHz('B', 3, etat_tube_fluo[2], REPETITIONS);
        }else if(std::chrono::system_clock::now()-time > std::chrono::seconds(3)){
            etat_tube_fluo[0] = 1;
            etat_tube_fluo[1] =  1;
            etat_tube_fluo[2] = 1;
            trans_trame_433MHz('D', 1, etat_tube_fluo[0], REPETITIONS);
            trans_trame_433MHz('C', 2, etat_tube_fluo[1], REPETITIONS);
            trans_trame_433MHz('B', 3, etat_tube_fluo[2], REPETITIONS);
        }
    }
  }
}

void Gestion::commande_radio(char tube_fluo, char *etat_tube_fluo){
    std::string couleur, status;
    int i=-1;

    switch(tube_fluo){
        case 'R':
            i=0;
            etat_tube_fluo[i] = !etat_tube_fluo[i];
            couleur="rouge";
            trans_trame_433MHz('D', 1, etat_tube_fluo[i], REPETITIONS);
        break;
        case 'V':
            i=1;
            etat_tube_fluo[i] = !etat_tube_fluo[i];
            couleur="vert";
            trans_trame_433MHz('C', 2, etat_tube_fluo[i], REPETITIONS);
            break;
        case 'B':
            i=2;
            etat_tube_fluo[i] = !etat_tube_fluo[i];
            couleur="bleu";
            trans_trame_433MHz('B', 3, etat_tube_fluo[i], REPETITIONS);
            break;
        default:
            return;
        break;
    }

    if(etat_tube_fluo[i]){
        status="allumé";
    }else{
        status="éteint";
    }

    std::cout << "Le tube fluorescent " << couleur << " est " << status << "\n";
}

 void Gestion::GPIO_1to0(int delai1, int delai0){
     pwm.set(true);
     usleep(delai1);
     pwm.set(false);
     usleep(delai0);
 }

void Gestion::trans_data_433MHz(char data){
    std::cout << data;
  switch(data){
    case '0':
        PWM_T1_T3(TREFH, TREFL);
        PWM_T3_T1(TREFH, TREFL);
        break;
    case '1':
        PWM_T1_T3(TREFH, TREFL);
        PWM_T1_T3(TREFH, TREFL);
        break;
    case '2':
        PWM_T3_T1(TREFH, TREFL);
        PWM_T3_T1(TREFH, TREFL);
        break;
    case 'S':
        PWM_T1_T32(TREFH, TREFL);
    break;
    default:
        break;
    }
}

void Gestion::trans_trame_433MHz(char maison, char objet, char activation, char repetition){
    while(repetition--){    
        for(const auto &i : trit[maison]) trans_data_433MHz(i);
        for(const auto &i : trit[objet]) trans_data_433MHz(i);
        for(const auto &i : TRIT_SEQ) trans_data_433MHz(i);
        trans_data_433MHz('0'+activation);
        trans_data_433MHz('S');
    }
}