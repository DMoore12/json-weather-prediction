#include <string>
#include <cmath>
#include "jsonParse.h"

float valMinusMean[101] = {0};

float simpleMean(int dataPointCount) {
  float add = 0;
  for(size_t i = 0; i < dataPointCount; i++) {
    add = add + valMinusMean[i];
  }
  return add / (dataPointCount - 1);
}

//Take the mean of the data type
float mean(std::string dataType, int dataPointCount, bool loadVals) {
  float add = 0;

  //Reset the value of valMinusMean[x]
  for(size_t i = 0; i <=101; i++) {
    valMinusMean[i] = 0;
  }

  //Compute the mean of the data type
  //Also, put the value into another variable for manipulation later
  if(dataType == "wind") {
    for(size_t i = 0; i < dataPointCount; i++) {
      add = add + wind[i];
      if(loadVals == true) {
      valMinusMean[i] = wind[i];
      }
    }
  } else if(dataType == "temp") {
    for(size_t i = 0; i < dataPointCount; i++) {
      add = add + temp[i];
      if(loadVals == true) {
      valMinusMean[i] = temp[i];
      }
    }
  } else {
    for(size_t i = 0; i < dataPointCount; i++) {
      add = add + humidity[i];
      if(loadVals == true) {
      valMinusMean[i] = humidity[i];
      }
    }
  }
      //Find the mean
      return add / dataPointCount;
}

void stdDevSubByMean(int dataPointCount, float currentMean) {
  for(size_t i = 0; i < dataPointCount; i++) {
    valMinusMean[i] = valMinusMean[i] - currentMean;
    valMinusMean[i] = valMinusMean[i] * valMinusMean[i];
  }
}

//Compute the standard deviation of the data type given
float stdDev(std::string dataType, int dataPointCount) {

  float complexMean = 0;
  float subByMean = 0;
  double stdDev = 0;

  //First, we need the mean of the data type
  complexMean = mean(dataType, dataPointCount, true);
  stdDevSubByMean(dataPointCount, complexMean);
  subByMean = simpleMean(dataPointCount);
  stdDev = sqrt(subByMean);
  return stdDev;
}
