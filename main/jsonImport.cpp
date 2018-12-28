#include <iostream>
#include <fstream>
#include <string>
#include "jsonImport.h"

using namespace std;

  //This string is set to the exact line count of weatherData.json... Remember, arrrays start at 0!
  string jsonString[169];
  int jsonLineCount;
  ifstream jsonTxt;

//This function will give (line by line) each line of the .JSON file
//This can then be decoded with jsonParse
void inTextLoad() {

  int i = 0;

  string filePath = "weatherData.json";

  jsonTxt.open(filePath);
    if(!jsonTxt)
      {
        cout << "Could not load the file!" << endl;
        return;
      }
  while(!jsonTxt.eof()){
    getline(jsonTxt, jsonString[i]);
    ++i;
  }
  jsonLineCount = i;
  jsonTxt.close();

  return;
}
