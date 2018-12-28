#ifndef JSON_PARSE
#define JSON_PARSE
/*
This header file and .cpp file are created directly for the HyperStation project.
This library should be used with an output of the same style as shows in 'weatherData.json'!
As you can see, this can handle up to 100 stations with up to 25 data point types!

We will use string logic to convert dataPointType's to new variables. The program will have
variables named the same as the data types in the .json file for easy use!
*/

#include <string>

//extern variable declarations
extern std::string stationID[101];
extern std::string dataPointType[26];

int featureCount(char featureToCount, std::string stringToCount);
void jsonCountParse();
void jsonDataParse();

#endif
