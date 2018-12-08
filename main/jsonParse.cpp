#include <string>
#include <nlohmann/json.hpp>

void jsonParse(std::string dataType) {

  using json = nhlomann::json;
  if(dataType == "temperature") {

  } else if(dataType == "humidity") {

  } else {

  }
  jsonAverage(dataPoint, dataType);
  return;
}

void jsonAverage(float dataPoint, std::string dataType) {

  return;
}
