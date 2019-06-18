#include "Gestion.hpp"

int main(int argc, char *argv[]){
  Gestion gestion;

  switch(argc){
    case 5:
      gestion.trans_trame_433MHz(
        *argv[1],
        std::atoi(argv[2]),
        std::atoi(argv[3]),
        std::atoi(argv[4])
      );
      break;
    default:
      while(true){
        gestion.selection();
      }
      break;
  }

  return EXIT_SUCCESS;
}