#ifndef JSON_PARSE
#define JSON_PARSE

extern float runningWind;
extern float runningTemp;
extern float runningHum;

void jsonParse(std::string dataType);
void jsonAverage(float dataPoint, std::string dataType);

#endif 
