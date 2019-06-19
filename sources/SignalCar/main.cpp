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
  int code_int;//tram
  std::string code;
  int taille_bande;
  if(argc >= 3){
    taille_bande=std::atoi(argv[2]);
    code_int=std::atoi(argv[1]);
  }else{
    taille_bande=256;
    code_int=0;
  }
  int repetition=10;
  for(; code_int<taille_bande+1 ; code_int++){
    //envoyer valeur
    code=convertisseur(code_int);
    if(!code.compare("00011000") || !code.compare("00100100") || !code.compare("01000010")){
      code_int++;
      code=convertisseur(code_int);
    }
    for(int j=0; j<repetition; j++){
      for(const auto &valeur : code){
        gestion.trans_data_433MHz(valeur);
      }
      gestion.trans_data_433MHz('1'); //allumer
      gestion.trans_data_433MHz('0'); //allumer
      gestion.trans_data_433MHz('0'); //allumer
      gestion.trans_data_433MHz(*argv[3]); //allumer
      gestion.trans_data_433MHz('S'); //fin
      usleep(1000);
      std::cout <<  " code: " << code_int << '\n';
    }
    usleep(500000);
  }

  //incrementer de 1
  return EXIT_SUCCESS;
}
