#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <ctime>
#include <math.h>
#include "GPIO.hpp"
#include "defines.hpp"
#include "Gestion.hpp"

std::string convertisseur (int decimal=0){
  int binaire;
  std::string tram = "";
  //8 = au nombre de valeur voulu dans la chaine pour decimal =1 binaire= 0000 0001
  for(int i=0 ; i < 8 ; i++){
    binaire=(decimal%2);
    tram=std::to_string(binaire)+tram;
    //std::cout << i <<" binaire: " << binaire << '\n';
    decimal=(decimal-binaire)/2;
  }
  //binaire=(decimal/1024)*10 //1
  //std::cout <<  " tram: " << tram << '\n';
  return  tram;
}

int main(int argc, char *argv[]){
  Gestion gestion;
  int code_int;//tram en decimal
  std::string code; //tram en binaire
  int taille_bande;
  //code_int = debut taille_bande=fin
  if(argc >= 3){
    taille_bande=std::atoi(argv[2]);
    code_int=std::atoi(argv[1]);
  }else{
    taille_bande=256;
    code_int=0;
  }
  //nb de fois qu'on fait l'envoie :
  int repetition=10;
  for(; code_int<taille_bande+1 ; code_int++){
    //envoyer la valeur :
    code=convertisseur(code_int); //conversion décimal en int
    //valeur a ne pas executer
    if(!code.compare("00011000") || !code.compare("00100100") || !code.compare("01000010")){
      code_int++;
      code=convertisseur(code_int);
    }
    //on envoie la valeur
    for(int j=0; j<repetition; j++){
      for(const auto &valeur : code){
        gestion.trans_data_433MHz(valeur);
      }
      //fin de la tram

      //les valeurs de la sequence:
      gestion.trans_data_433MHz('0');
      gestion.trans_data_433MHz('1');
      gestion.trans_data_433MHz('1');

      gestion.trans_data_433MHz(*argv[3]); //allumer ou eteint
      gestion.trans_data_433MHz('S'); //fin
      usleep(1000);//temps entre les tram
      std::cout <<  " code: " << code_int << '\n';
    }
    usleep(1000000); //1 sec entre chaque nouveau code
  }

  return EXIT_SUCCESS;
}
