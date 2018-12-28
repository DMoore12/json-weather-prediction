#include <string>
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

//Count how many of a feature (character) there are in a string
int featureCount(char featureToCount, std::string stringToCount) {
  int stringToCountLength = stringToCount.length();
  int returnValue = 0;
  for(size_t i = 0; i <= stringToCountLength; ++i) {
    if(stringToCount[i] == featureToCount) {
      ++returnValue;
    }
  }
  return returnValue;
}

//Parse the data points to see how many of each there are
void jsonCountParse(std::string dataType, std::string stringToParse) {

}

void jsonDataParse() {

}
