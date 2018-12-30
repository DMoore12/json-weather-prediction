#include <string>
#include <sstream>

#include "jsonImport.h"
#include "jsonParse.h"


/*
What we have:
  A lot of strings in jsonString[169] (168 strings to be exact!)
  An integer with exactly how many strings there are to test in jsonLineCount

What we want to do:
  Setup a function to count how many of a certain char there are (for determining data point counts!)
  Setup a function to determine full data points
    This needs to be broken down into...
      Station ID
      Data Point Type
      Data Point

From here, we can determine whether or not there is a storm coming by running descriptive statistics!
*/

//Variable declarations from jsonParse.h for use in other .cpp files
float wind[101];
float temp[101];
float humidity[101];
int dataSlot;

//Count how many of a feature (character) there are in a string
//To be used to count {'s to determine how many valid data points there are
int featureCount(char featureToCount, std::string stringToCount) {
  int stringToCountLength = stringToCount.length();
  int returnValue = 0;
  dataSlot = 0;
  for(size_t i = 0; i <= stringToCountLength; i++) {
    if(stringToCount[i] == featureToCount) {
      ++returnValue;
    }
  }
  return returnValue;
}

//Parse the data points to see how many of each there are
int jsonCountAndParse(std::string dataType, std::string stringToParse) {
  std::string parsedDataType;
  std::string dataToSave;
  int returnCount = 0;
  int pos;
  for(size_t i = 12; i < 12 + dataType.length(); i++) {
    parsedDataType.push_back(stringToParse[i]);
    pos = i;
  }
  if(parsedDataType == dataType) {
    returnCount++;
    pos = pos + 16;

//Logic for finding data...
  int findPos = stringToParse.find('}', pos);
  while(pos != findPos) {
    dataToSave.push_back(stringToParse[pos]);
    pos++;

  }

    std::stringstream convert(dataToSave);
    if(dataType == "wind") {
      convert >> wind[dataSlot];
    } else if(dataType == "temp") {
      convert >> temp[dataSlot];
    } else {
      convert >> humidity[dataSlot];
    }
  }
  return returnCount;
}
