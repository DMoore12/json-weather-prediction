#include <iostream>

//Run a terminal-esque function to allow the user to decide what the program is to do
//It returns 'int' so main can deicde whether or not to quit
int terminal() {
  //Save some time by not having to put 'std::'
  using namespace std;

  //Variable defs
  string input;

  cout << "Type 'quit' to quit. " << endl << "Type 'run' to run the JSON updater" << endl;
  cin >> input;
  //Check what the input is and allow for some error in typing and return a value to tell main() what to call
  if(input == "quit" || input == " quit" || input == "quit "){
    return 0;
  } else if(input == "run" || input == " run" || input == "run "){
    return 2;
  } else {
    return 3;
  }
}
