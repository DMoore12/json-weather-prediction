#include <iostream>
#include <string>
#include <cstddef>

#include "jsonImport.h"
#include "jsonParse.h"

//Prototypes. Will hopefully end up as .h files
int terminal();
void runLoop();
void help();

//Functions for calling

//Main Function
int main() {
  terminalLoop:

  switch(terminal()){
    case 0:
      return 0;
      exit(0);

    case 1:
      help();
      goto terminalLoop;

    case 2:
      runLoop();
      break;

    case 3:
      std::cout << "Incorrect value entered!" << std::endl;
      goto terminalLoop;

  }

  return 0;
}
