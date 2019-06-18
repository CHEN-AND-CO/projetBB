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
  for(int i=0 ; i < 11 ; i++){
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
  int taille_bande=1635;
  int repetition=10;
  for(code_int=1630 ; code_int<taille_bande+1 ; code_int++){
    //envoyer valeur
    code=convertisseur(code_int);
    for(int j=0; j<repetition; j++){
      for(const auto &valeur : code){
        gestion.trans_data_433MHz(valeur);
      }
      gestion.trans_data_433MHz('0'); //allumer
      gestion.trans_data_433MHz('S'); //fin

      std::cout <<  " code: " << code_int << '\n';
    }
    usleep(10000);
  }

  //incrementer de 1
  return EXIT_SUCCESS;
}
