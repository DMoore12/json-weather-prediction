#include <iostream>
#include <fstream>
#include <string>
#include "jsonImport.h"

using namespace std;

  //This string is set to the exact line count of weatherData.json... Remember, arrrays start at 0!
  string jsonString[169];
  int jsonLineCount;

void inTextLoad() {

  int i = 0;

  string filePath = "weatherData.json";

  ifstream txt (filePath);
    if(!txt)
      {
        cout << "Could not load the file!" << endl;
        return;
      }
  while(!txt.eof()){
    getline (txt, jsonString[i]);
    ++i;
  }
  jsonLineCount = i;
  txt.close();

  return;
}
