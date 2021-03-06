#include "Gestion.hpp"

Gestion::Gestion(): r{GPIO_RED}, v{GPIO_GREEN}, b{GPIO_BLUE}, bp{GPIO_BP, GPIO::IN}, pwm{GPIO_QAM}, an{AN_POTAR}, tube_fluo{'R'}, trit{256, ""} {
    etat_tube_fluo = new char[256];

    etat_tube_fluo['R'] = 1;
    etat_tube_fluo['V'] = 1;
    etat_tube_fluo['B'] = 1;

    trit['A'] = TRIT_A;
    trit['B'] = TRIT_B;
    trit['C'] = TRIT_C;
    trit['D'] = TRIT_D;
    trit[1]   = TRIT_1;
    trit[2]   = TRIT_2;
    trit[3]   = TRIT_3;
}

void Gestion::selection(){
  auto valeurPotentiometre=an.read();

  if(valeurPotentiometre<=600){
    tube_fluo='R';
    r.on();
    v.off();
    b.off();

    if(etat_tube_fluo[(int)tube_fluo]){
        r.setLimit(3);
    }else{
        r.setLimit(10);
    }
  }else if(valeurPotentiometre<=1200){
    tube_fluo='V';
    r.off();
    v.on();
    b.off();

    if(etat_tube_fluo[(int)tube_fluo]){
        v.setLimit(3);
    }else{
        v.setLimit(10);
    }
  }else{
    tube_fluo='B';
    r.off();
    v.off();
    b.on();

    if(etat_tube_fluo[(int)tube_fluo]){
        b.setLimit(3);
    }else{
        b.setLimit(10);
    }
  }

  if(!bp.get()){
    auto time = std::chrono::system_clock::now();
    while(!bp.get());
    if(std::chrono::system_clock::now()-time > std::chrono::seconds(4)){
        etat_tube_fluo['R'] = 0;
        etat_tube_fluo['V'] = 0;
        etat_tube_fluo['B'] = 0;
        commande_radio('R', etat_tube_fluo);
        commande_radio('V', etat_tube_fluo);
        commande_radio('B', etat_tube_fluo);
    }else if(std::chrono::system_clock::now()-time > std::chrono::seconds(2)){
        etat_tube_fluo['R'] = 1;
        etat_tube_fluo['V'] = 1;
        etat_tube_fluo['B'] = 1;
        commande_radio('R', etat_tube_fluo);
        commande_radio('V', etat_tube_fluo);
        commande_radio('B', etat_tube_fluo);
    }else{
        commande_radio(tube_fluo,etat_tube_fluo);
    }
  }
}

void Gestion::commande_radio(char tube_fluo, char *etat_tube_fluo){
    std::string couleur, status;
    
    etat_tube_fluo[(int)tube_fluo] = !etat_tube_fluo[(int)tube_fluo];

    switch(tube_fluo){
        case 'R':
            couleur="rouge";
            trans_trame_433MHz('D', 1, etat_tube_fluo[(int)tube_fluo], REPETITIONS);
        break;
        case 'V':
            couleur="vert";
            trans_trame_433MHz('C', 2, etat_tube_fluo[(int)tube_fluo], REPETITIONS);
            break;
        case 'B':
            couleur="bleu";
            trans_trame_433MHz('B', 3, etat_tube_fluo[(int)tube_fluo], REPETITIONS);
            break;
        default:
            return;
        break;
    }

    if(!etat_tube_fluo[(int)tube_fluo]){
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
        usleep(1000);
        std::cout << "\n";
    }
}

void Gestion::trans_trame2_433MHz(char maison, char objet, char activation, char repetition){
    while(repetition--){    
        for(const auto &i : convertisseur(maison-'A', 4)) trans_data_433MHz(i);
        for(const auto &i : convertisseur(objet, 4)) trans_data_433MHz(i);
        for(const auto &i : TRIT_SEQ2) trans_data_433MHz(i);
        trans_data_433MHz('0'+activation);
        trans_data_433MHz('S');
        usleep(1000);
        std::cout << "\n";
    }
}

std::string Gestion::convertisseur (int decimal, int bits){
  int binaire;
  std::string tram = "";

  for(int i=0 ; i < bits ; i++){
    binaire=(decimal%2);
    tram=std::to_string(binaire)+tram;
    decimal=(decimal-binaire)/2;
  }

  return  tram;
}

void Gestion::commande_radio_manuelle(char tube_fluo, int etat){
    etat_tube_fluo[(int)tube_fluo] = etat;
    switch(tube_fluo){
        case 'R':
            trans_trame_433MHz('D', 1, etat_tube_fluo[(int)tube_fluo], REPETITIONS);
        break;
        case 'V':
            trans_trame_433MHz('C', 2, etat_tube_fluo[(int)tube_fluo], REPETITIONS);
            break;
        case 'B':
            trans_trame_433MHz('B', 3, etat_tube_fluo[(int)tube_fluo], REPETITIONS);
            break;
        default:
            return;
        break;
    }
}

void Gestion::recherche(int debut, int longueur, int etat, int limit){
    std::string code;
    for(; debut < longueur ; debut++){
        code=convertisseur(debut, limit);

        for(auto j = 0; j < REPETITIONS; j++){
            for(const auto &valeur : code)  trans_data_433MHz(valeur);
            for(auto i = 0; i < 11-limit; i++) trans_data_433MHz('1');
            trans_data_433MHz('0'+etat);
            trans_data_433MHz('S');
            usleep(1000);
            std::cout <<  " code: " << debut << '\n';
        }
    usleep(500000);
    }
}