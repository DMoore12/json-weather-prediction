#include <iostream>
#include <string>

#include "jsonImport.h"
#include "jsonParse.h"

using namespace std;

string stringToSend;
int dataPointCount;
int stationCount;

void runLoop() {
  inTextLoad();
  for (size_t i = 0; i <= jsonLineCount; i++) {
    stringToSend = jsonString[i];
    dataPointCount = dataPointCount + featureCount('{', stringToSend);
  }
  cout << "There are " << dataPointCount << " data points!" << endl;
}
