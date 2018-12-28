#include <iostream>
#include <string>

#include "jsonImport.h"
#include "jsonParse.h"

using namespace std;

string stringToSend;
int dataTypeCount;
int dataPointCount[3];

void runLoop() {
  inTextLoad();
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataTypeCount = dataTypeCount + featureCount('{', stringToSend);
  }
  cout << "There are " << dataTypeCount << " data points!" << endl;
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataPointCount[0] = dataPointCount[0] + jsonCountParse("wind", stringToSend);
  }
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataPointCount[1] = dataPointCount[1] + jsonCountParse("temp", stringToSend);
  }
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataPointCount[2] = dataPointCount[2] + jsonCountParse("humidity", stringToSend);
  }
  cout << "There are " << dataPointCount[0] << " wind data points" << endl;
  cout << "There are " << dataPointCount[1] << " temperature data points" << endl;
  cout << "There are " << dataPointCount[2] << " humidity data points" << endl;
}
