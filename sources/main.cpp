#include "Gestion.hpp"

int main(int argc, char *argv[]){
  Gestion gestion;

  switch(argc){
    case 5:
      std::cout << "maison=" << *argv[1] 
                << "\t objet=" << std::atoi(argv[2])
                << "\t activation=" << std::atoi(argv[3])
                << "\t repetitions=" << std::atoi(argv[4])
                << "\n";
      gestion.trans_trame_433MHz(
        *argv[1],
        std::atoi(argv[2]),
        !std::atoi(argv[3]),
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