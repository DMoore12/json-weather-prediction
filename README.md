# Command Line Adverse Weather Prediction Service

[![Build Status](https://travis-ci.org/DMoore12/json-weather-prediction.svg?branch=master)](https://travis-ci.org/DMoore12/json-weather-prediction.svg?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/626cbebaed784901a96dc44901006708)](https://www.codacy.com/app/DMoore12/json-weather-prediction?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DMoore12/json-weather-prediction&amp;utm_campaign=Badge_Grade)
[![](https://img.shields.io/github/license/DMoore12/json-weather-prediction.svg)](https://www.apache.org/licenses/LICENSE-2.0)
[![Testing Badge](https://img.shields.io/badge/-algorithm%20testing%20incomplete-yellow.svg?logo=github)]()

---

#### *Project Timeline:*

-   [x] Project is buildable
-   [x] Project can load .json files
-   [x] Project can parse .json files for use
-   [x] Project works as advertised
-   [x] Setup basic Travis
-   [x] Documentation provided
-   [ ] Add probability output of some sort for practical use
-   [ ] Test and fine tune algorithm

#### *Extra Changes:*

-   [ ] Add text/email notifications when a storm begins
-   [ ] Convert arrays to vectors
-   [ ] Remove data file size limits
-   [ ] Convert to database use rather than .json
-   [ ] Add location bias
-   [ ] Mark when a cold front is approaching

json-weather-prediction is an application that will intake a .json file (with contents that don't *technically* fit `JSON` standards) and output probability of a thunderstorm based on the data inside. It will be designed for use on a Raspberry Pi terminal, but will hopefully be available for more than just this use. It's initial production was designed for use with the [HyperStation.](https://github.com/russelltg/weatherstation) However, this project does not actually save .json files, so future implementation might shift away from reading .json files.

***Once started, the application will run infinitely until closed.*** Since it is designed to run on a platform that begins crunching data from the second it boots to the second the power is cut, this is the intended behavior.

---

## ***Current Features:***

The project:
-   Can load `.json` files up to 500 lines long and interpret wind, humidity, and temperature data
-   Can take averages of data points and standard deviation of data for easy processing
-   Can determine wind strength using the [Beaufort Scale](https://www.spc.noaa.gov/faq/tornado/beaufort.html)
-   Can calculate current dewpoint when humidity is greater than 50%

Thunderstorm detecting functionality is currently being developed and tested.

---

A makefile is included for easy building. However, it is contained in a different directory than the output. If the program is not run from the directory the executable is contained in, the loading of the data will fail. For this reason, `build.sh` is included. This will build the project using the makefile, change the directory to that of the executable, and run it.

The .json file, `weatherData.json`, is contained in the same directory as the executable and follows the format of the [HyperStation project.](https://github.com/russelltg/weatherstation) This format is as follows:

```JSON
{"sensor" : "wind" , "reading" : 5}
{"sensor" : "temp" , "reading" : 20}
{"sensor" : "humidity" , "reading" : 60}
```

While this format isn't technically a valid .json file, each line itself is valid `JSON`. This format is simply used as the weather station this project is compatible uses sends `JSON` line by line.

Note: This format assumes wind data is in km/hr, temperature data is in degrees C, and humidity is a percentage.

The project does not use a standard .json parser, so it cannot accept *any* data. All data must be in the format above. However, the project should be able to accept other data types. It will just ignore these as they aren't useful for the [HyperStation.](https://github.com/russelltg/weatherstation)

Travis ci can be found [here.](https://travis-ci.org/DMoore12/json-weather-prediction#)

---

## ***How the Prediction Works:***

The prediction service uses a mathematical model to guess the likelihood of a storm of some sort based on the weather data given. This model uses a couple of metrics. These metrics are give in the table below:

|Metric|Purpose|Importance (1-5)|
|:---|---|:---:|
|**Average Wind Speed (km/hr)**|To use the [Beaufort Scale](https://www.spc.noaa.gov/faq/tornado/beaufort.html) to determine wind severity|*5*|
|**Average Temperature**|To allow for basic predictions as to if a storm is possible|*1*|
|**Average Humidity**|To allow for more complex prediction based on known storm compositions|*5*|
|**Wind Standard Deviation**|To predict storm volatility an decide whether a storm is approaching before it begins|*4*|
|**Temperature Standard Deviation**|To predict if a cold front is approaching|*2*|
|**Humidity Standard Deviation**|To predict weather patterns|*1*|
|**Dewpoint**|To determine if surface conditions exist for a thunderstorm to occur|*5*|

The model uses a more complex version of the simple importance weighting system to determine which phase a storm is in, if one is present at all. Items with low weights are not currently used in the model. They have only been implemented for future systems to use.

The system is based on a score from 0 - 100 with 100 being a very high probability of a storm occuring. The wind category, temperature, humidity, and dewpoint are all assign weights based on the importance above. All of their importances added comes to 16. Each metric will have a certain amount of points of 100 assigned to it to represent its importance level of the overall decision. Therefore, each importance level the metric has will account for 6.25 points on the scale. Knowing this, the wind category on the [Beaufort Scale](https://www.spc.noaa.gov/faq/tornado/beaufort.html), average humidity, and dewpoint will all be worth 31.25 points. Average temperature will be worth 6.25. Using this method, each will be set inside their own bounds and contribute to one final number.

#### ***The Wind Metric:***

Each section is evaluated and recieves an `probability score`. The `probability scores` are added to find, out of 100%, the calculated probability that a thunderstorm is approaching. This is refered to as the alert score for each. 

>***Note, that extreme conditions could produce a total probability value over 100***

The wind metric combines average wind speed with the wind standard deviation. Average wind data is converted to a category by using the [Beaufort Scale](https://www.spc.noaa.gov/faq/tornado/beaufort.html). This is what the scale looks like:

|Category|Wind Speed (km/hr)|Title|Probability Score|
|:---:|:---|:---|:---|
|0|0-2|Calm|0|
|1|3-5|Light Air|0|
|2|6-11|Light Breeze|0|
|3|12-19|Gentle Breeze|0|
|4|20-28|Moderate Breeze|0|
|5|29-38|Fresh Breeze|13.02083333|
|6|39-49|Strong Breeze|15.625|
|7|50-61|High Wind, Moderate Gale, Near Gale|18.22916667|
|8|62-74|Gale, Fresh Gale|20.83333334|
|9|75-88|Strong/Severe Gale|23.4375|
|10|89-102|Storm/Whole Gale|26.04166667|
|11|103-117|Violent Storm|28.64583334|
|12|>117|Hurricane Force|31.25|

The `probability score` is found by multiplying the category by 2.604166667. This means that if the winds are at the 12 level, the category will hold a value of 31.25, the highest possible value for the wind category total as denoted by the importance level. Levels 4 and lower are not conducive to storms, so they do not recieve a score. This is due to the fact that the average storm ranges from categories 6-10. 5 is added in as a buffer as a storm might occur, but below category 4, a front is approaching rather than a storm.

If the sample standard deviation of the wind is greater than or equal to 5 km/hr, then a bonus is applied to the score to show the volatility of the wind. If the wind recieves a category of 13-25 on the scale, this means that it is a volatile wind. 

>Categories 14-25 mirror 0-12 on the Beaufort Scale with 14 being calm and 25 being a hurricane like force.

If the category is larger than 17, the score will be calculated just like above but a bonus of 5 points will be added. Volatile wind ranks as if it were two categories higher.

The implementation in the code looks like this:

```C++
if(windCategory <= 4) {
    windScore = 0;
  } else if(windCategory > 17) {
    windScore = ( (windCategory - 13) * 2.604166667) + 5;
  } else {
    windScore =  windCategory * 2.604166667;
  }
```

#### ***The Temperature Metric:***

Temperature isn't great for predicting a storm. Generally, storms require both warm air at the surface and cold air slightly elevated for form a storm. Therefore, if the surface temperature is above 13 °C, this metric will recieve 6.25 points, its full total. For each °C under 13 the average temperature is, the score will drop by 0.48076923076. This means that at 0 °C, the score is 0 as thunderstorms are essentially impossible to form. And, as the temperature approaches 13 °C, the score will approach the full 6.25.

The implementation in the code looks like this:

```C++
if(tempAve >= 13) {
    temperatureScore = 6.25;
  } else if(tempAve < 0) {
    temperatureScore = 0;
  } else {
    temperatureScore = tempAve * 0.48076923076;
  }
```

#### ***The Humidity Metric:***

Humidity levels of 80% or more are conducive to thunderstorm creation. Therefore, values at 80% or above will get the full 31.25 points of the category. The bottom cutoff will be 20% as a thunderstorm is virtually impossible to form at such a condition. The points will drop in a linear fashion betwen 20% and 80%, completing the scale. Therefore, each 1% the humidity falls causes the score to drop by 0.52083333333.

The implementation in the code looks like this:

```C++
if(humAve >= 80) {
    humidityScore = 31.25;
  } else if(humAve <=20) {
    humidityScore = 0;
  } else {
    humidityScore = (humAve - 20) * 0.52083333333;
  }
```

#### ***The Dewpoint Metric:***

Dewpoint, as a general rule, needs to be 55 °F (12.7778 °C) for a surface based thunderstorm to occur ([Source](http://www.theweatherprediction.com/habyhints/141/)). This doesn't mean that a storm cannot occur below this mark, but rather that it is very unlikely. Therefore, values above 65 °F (18.3333 °C) will recieve a full 31.25 points. Values between 55 °F and 65°F (12.7778 °C - 18.3333 °C) will recieve between 23.4375 ([3/4]*31.25) and 31.25 points. The point totals will then fall linearly to 0 when the temperature is 32 °F (0 °C) from 10. This means that for a dewpoint lower than 12.7778, the highest value that can be obtained is 10. This is due to the fact that surface thunderstorms are basically impossible to form under 55 °F (12.7778 °C). There is a way for them to form, but the likelihood of that occuring is very, very low. Allowing the ceiling of a low dewpoint score to be in the 20's is misleading.

Most of the time, this metric will return a somewhat

The implementation in the code looks like this:

```C++
if(dewPoint >= 18.3333) {
    dewpointScore = 31.25;
  } else if(dewPoint >= 12.7778) {
    dewpointScore = ( (dewPoint - 12.7778) * 4.21879218792) + 23.4375
  } else if(dewPoint <= 0) {
    dewpointScore = 0;
  } else {
    dewpointScore = dewPoint * 0.83333333333
  }
```