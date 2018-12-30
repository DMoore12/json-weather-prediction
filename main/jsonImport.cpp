#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "jsonImport.h"

using namespace std;

  //This string is set to the exact line count of weatherData.json... Remember, arrrays start at 0!
  string jsonString[501];
  int jsonLineCount;
  int lineOverflowStop = 0;
  ifstream jsonTxt;

//This function will give (line by line) each line of the .JSON file
//This can then be decoded with jsonParse
void inTextLoad() {

  int i = 0;

  //The executable is in '//Users//dawsonmoore//Documents//Coding//json-weather-prediction//main//'
  //We must go up one!
  char buf[255];
  getcwd(buf, sizeof(buf));
  cout << "The CWD is " << buf << endl;
  jsonTxt.open("weatherData.json");
    if(!jsonTxt)
      {
        cout << "Could not load the file!" << endl;
        cout << "Attempting to create a file to load!"  << endl;
        inTextCreate();
        jsonTxt.open("weatherData.json");
        if(!jsonTxt) {
          cout << "Could not create file!" <<endl;
        }
        return;
      }

  while(!jsonTxt.eof()){
    if(i >= 500) {
      cout << "There are too many data points in weatherData.json!" << endl;
      jsonLineCount = i;
      jsonTxt.close();
      return;
    }
    getline(jsonTxt, jsonString[i]);
    ++i;
  }
  jsonLineCount = i;
  jsonTxt.close();

  return;
}

void inTextCreate() {
  ofstream jsonTxtOut;
  jsonTxtOut.open("weatherData.json");
  jsonTxtOut.close();

  return;
}
