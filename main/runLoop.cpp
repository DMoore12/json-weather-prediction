#include <string>

//REMOVE
#include <iostream>

#include "jsonImport.h"
#include "jsonParse.h"

float mean(std::string dataType, int dataPointCount, bool loadVals);
float stdDev(std::string dataType, int dataPointCount);
float dewpointCalc(float averageHumidity, float averageTemperature);
int windCategorize(float averageWind, float windDeviation);

using namespace std;

string stringToSend;
int dataTypeCount;
int dataPointCount[3];
int countResult;
int startLine = 0;
int linePos;

void runLoop() {

  inTextLoad();

  //Set all vars to 0 to stop overflow
  dataTypeCount = 0;
  for(size_t i = 0; i < 3; i++) {
    dataPointCount[i] = 0;
  }
  countResult = 0;

  //Start the counting...
  for (int i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataTypeCount = dataTypeCount + featureCount('{', stringToSend);
  }

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
  linePos = startLine ;
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
}

void predictThunderstorm() {
  float windDev, tempDev, humDev, windAve, tempAve, humAve; 
  float dewPoint = 0;
  int windCategory;
  float tsLikelihood;
  windDev = stdDev("wind", dataPointCount[0]);
  cout << "windDev = " << windDev << "!" << endl;
  tempDev = stdDev("temp", dataPointCount[1]);
  cout << "tempDev = " << tempDev << "!" << endl;
  humDev = stdDev("humidity", dataPointCount[2]);
  cout << "humDev = " << humDev << "!" << endl;
  windAve = mean("wind", dataPointCount[0], false);
  cout << "Wind average: " << windAve << endl; 
  tempAve = mean("temp", dataPointCount[1], false);
  cout << "Temp average: " << tempAve << endl;
  humAve = mean("humidity", dataPointCount[2], false);
  cout << "Humidity average: " << humAve << endl;
  if(humAve >= 50) {
  dewPoint = dewpointCalc(humAve, tempAve);
  cout << "The dewpoint is: " << dewPoint << endl;
  } else {
    cout << "The humidity is too low to have a thunderstorm!" << endl;
  }
  windCategory = windCategorize(windAve, windDev);
  cout << "The current wind category is: " << windCategory << endl;
  float windScore, temperatureScore, humidityScore, dewpointScore = 0;
  if(windCategory <= 4) {
    windScore = 0;
  } else if(windCategory > 17) {
    windScore = ( (windCategory - 13) * 2.604166667) + 5;
  } else {
    windScore =  windCategory * 2.604166667;
  }
  if(tempAve >= 13) {
    temperatureScore = 6.25;
  } else if(tempAve < 0) {
    temperatureScore = 0;
  } else {
    temperatureScore = tempAve * 0.48076923076;
  }
  if(humAve >= 80) {
    humidityScore = 31.25;
  } else if(humAve <=20) {
    humidityScore = 0;
  } else {
    humidityScore = (humAve - 20) * 0.52083333333;
  }
  if(dewPoint >= 18.3333) {
    dewpointScore = 31.25;
  } else if(dewPoint >= 12.7778) {
    dewpointScore = ( (dewPoint - 12.7778) * 4.21879218792) + 23.4375;
  } else if(dewPoint <= 0) {
    dewpointScore = 0;
  } else {
    dewpointScore = dewPoint * 0.83333333333;
  }

  tsLikelihood = windScore + temperatureScore + humidityScore + dewpointScore;
  cout << "The wind score is " << windScore << endl;
  cout << "The temperature score is " << temperatureScore << endl;
  cout << "The humidity score is " << humidityScore << endl;
  cout << "The dewpoint score is " << dewpointScore << endl;
  cout << "The likelihood of a thunderstorm is " << tsLikelihood << "%" << endl << endl << endl;
  return;
}
