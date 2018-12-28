#include <iostream>
#include <string>

#include "jsonImport.h"
#include "jsonParse.h"

using namespace std;

string stringToSend;
int dataTypeCount;
int dataPointCount[3];
int countResult;
int currentLine = 0;
//float wind[101];
//float temp[101];
//float humidity[101];

void runLoop() {
  inTextLoad();
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataTypeCount = dataTypeCount + featureCount('{', stringToSend);
  }
  cout << "There are " << dataTypeCount << " data points!" << endl;
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    countResult = jsonCountAndParse("wind", stringToSend);
    dataPointCount[0] = dataPointCount[0] + countResult;
    if(countResult != 0) {
      dataSlot++;
    }
  }
  currentLine = 0;
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataPointCount[1] = dataPointCount[1] + jsonCountAndParse("temp", stringToSend);
  }
  currentLine = 0;
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataPointCount[2] = dataPointCount[2] + jsonCountAndParse("humidity", stringToSend);
  }
  cout << "There are " << dataPointCount[0] << " wind data points" << endl;
  cout << "There are " << dataPointCount[1] << " temperature data points" << endl;
  cout << "There are " << dataPointCount[2] << " humidity data points" << endl;
  for(size_t i = 0; i <= 10; i++) {
    cout << "Wind data point " << i << " is " << wind[i] << endl;
  }
}
