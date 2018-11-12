#include <iostream>
#include <string>

#include "jsonImport.h"

using namespace std;

string path = "/";

int inTextLoad();

void runLoop() {
  cout << "RUNNING. . ." << endl;
  inTextLoad();

  //Create a char for the input and set the standard to do nothing if the user skips the inpt.
  char debugChoicerunLoop = 'n';

debugChoice:

  //See if the user would like to visually confirm the loading of the data... Good for debugging!
  cout << "Would you like to see the contents of 'weatherData.json? (y/n)'" << endl;
  cin >> debugChoicerunLoop;
  if (cin.fail()){
    cout << "Incorrect choice!" << endl;
    goto debugChoice;
  } else if(debugChoicerunLoop == 'y'){
    int i = jsonLineCount;
    while(i != 0){
      cout << jsonString[i] << endl;
    }
  }
}
