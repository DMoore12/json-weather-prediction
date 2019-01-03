#include <iostream>

//This file defines the methods for determining the probability of a thunderstorm
float dewpointCalc(float averageHumidity, float averageTemperature) {
    float dewPoint = averageTemperature - ( (100 - averageHumidity) / 5);
    return dewPoint;
}

//Take in a float and return an int (kind of like tornado rankings...)
int windCategorize(float averageWind, float windDeviation) {

/*
    Wind categories:
    The scale is from 0 - 12 with 0 being low wind and 12 being high wind. There are two scales build into this function.
    The first is from 0 - 12. The second is from 13 - 25.
    0 - 12 is for constant winds with a low deviation. This means that there hasn't been a large shift in the data meaning either the storm has been in progress or has not begun.
    This can be used to aid a notification service. If a data range comes from 13 - 25, that means winds are rapidly shifting. In such a case, this is a good indicator that a storm is starting.
    This can be used to send notifications when a storm is actually beginning, not just when it is likely to be occurring!
    This model will the Beaufort Scale for determining wind severity.

    Ranges:
    0: 0-2 km/hr (Calm)
    1: 3-5 km/hr (Light Air)
    2: 6-11 km/hr (Light Breeze)
    3: 12-19 km/hr (Gentle Breeze)
    4: 20-28 km/hr (Moderate Breeze)
    5: 29-38 km/hr (Fresh Breeze)
    6: 39-49 km/hr (Strong Breeze)
    7: 50-61 km/hr (High Wind, Moderate Gale, Near Gale)
    8: 62-74 km/hr (Gale, Fresh Gale)
    9: 75-88 km/hr (Stong/Severe Gale)
    10: 89-102 km/hr (Storm/Whole Gale)
    11: 103-117 km/hr (Violent Storm)
    12: >117 km/hr (Hurriane Force)

    Cases 6 and 7 are considered 'advisory level'.
    Cases 8-12 will be full blown thunderstorm notification worthy.
*/

int category = 0;

//Yes, I know this is ugly... Reminder to myself to change it later...
if(averageWind <= 2) {
        category = 0;
    } else if(averageWind > 2 && averageWind <= 5) {
        category = 1;
    } else if(averageWind > 5 && averageWind <=11) {
        category = 2;
    } else if(averageWind > 11 && averageWind <=19) {
        category = 3;
    } else if(averageWind > 19 && averageWind <=28) {
        category = 4;
    } else if(averageWind > 28 && averageWind <=38) {
        category = 5;
    } else if(averageWind > 38 && averageWind <=49) {
        category = 6;
    } else if(averageWind > 49 && averageWind <=61) {
        category = 7;
    } else if(averageWind > 61 && averageWind <=74) {
        category = 8;
    } else if(averageWind > 74 && averageWind <=88) {
        category = 9;
    } else if(averageWind > 88 && averageWind <=103) {
        category = 10;
    } else if(averageWind > 103 && averageWind <=117) {
        category = 11;
    } else {
        category = 12;
    }
    if(windDeviation >= 5) {
        category = category + 13;
    }
    return category;
}
