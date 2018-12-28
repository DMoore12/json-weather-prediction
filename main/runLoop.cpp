#include <iostream>
#include <string>

#include "jsonImport.h"
#include "jsonParse.h"

using namespace std;

string stringToSend;
int dataTypeCount;
int dataPointCount[3];
int countResult;
int startLine = 0;
int linePos;

void runLoop() {

  //***REMEMBER TO REMOVE DEBUG CONSOLE PRINTS FOR BETTER PERFORMANCE!!!***


  inTextLoad();

  //Set all vars to 0 to stop overflow
  dataTypeCount = 0;
  for(size_t i = 0; i < 3; i++) {
    dataPointCount[i] = 0;
  }
  countResult = 0;

  //Start the counting...
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataTypeCount = dataTypeCount + featureCount('{', stringToSend);
  }
  cout << "There are " << dataTypeCount << " data points!" << endl;

  //Starline logic
  if(jsonLineCount > 150) {
    startLine = jsonLineCount - 150;
  }

  //This format will only intake the last 150 lines. This should allow 50 of each data type
  //The variables storing the data are initialized to 101 to account for error in the arduino
  //Send protocol. I should use std::vector, but that's above my paygrade at the moment :)
  linePos = startLine;
  dataSlot = 0;
  while(linePos <= jsonLineCount) {
    stringToSend = jsonString[linePos];
    countResult = jsonCountAndParse("wind", stringToSend);
    dataPointCount[0] = dataPointCount[0] + countResult;
    if(countResult != 0) {
      dataSlot++;
    }
    linePos++;
  }
  linePos = startLine;
  dataSlot = 0;
  while(linePos <= jsonLineCount) {
    stringToSend = jsonString[linePos];
    countResult = jsonCountAndParse("temp", stringToSend);
    dataPointCount[1] = dataPointCount[1] + countResult;
    if(countResult != 0) {
      dataSlot++;
    }
    linePos++;
  }
  linePos = startLine;
  dataSlot = 0;
  while(linePos <= jsonLineCount) {
    stringToSend = jsonString[linePos];
    countResult = jsonCountAndParse("humidity", stringToSend);
    dataPointCount[2] = dataPointCount[2] + countResult;
    if(countResult != 0) {
      dataSlot++;
    }
    linePos++;
  }

  cout << "There are " << dataPointCount[0] << " wind data points" << endl;
  cout << "There are " << dataPointCount[1] << " temperature data points" << endl;
  cout << "There are " << dataPointCount[2] << " humidity data points" << endl;
  for(size_t i = 0; i <= 10; i++) {
    cout << "Wind data point " << i << " is " << wind[i] << endl;
  }
  for(size_t i = 0; i<=10; i++) {
    cout << "Temperature data point " << i << " is " << temp[i] << endl;
  }
  for(size_t i = 0; i<=10; i++) {
    cout << "Humidity data point " << i << " is " << humidity[i] << endl;
   }
}

void predictThunderstorm() {
  int i = 0;
  i = i + 1;
  return;
}
