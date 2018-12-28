#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
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

  //The executable is in '//Users//dawsonmoore//Documents//Coding//json-weather-prediction//main//'
  //We must go up one!
  char buf[255];
  string toAdd;
  getcwd(buf, sizeof(buf));
  toAdd = buf;
  cout << "The CWD is " << buf << endl;
  jsonTxt.open("weatherData.json");
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
