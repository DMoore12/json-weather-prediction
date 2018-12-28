# Command Line Weather Prediction Service

[![HitCount](http://hits.dwyl.com/{dmoore12}/{json-weather-prediction}.svg)](http://hits.dwyl.com/{dmoore12}/{json-weather-prediction})
[![Build Status](https://travis-ci.org/DMoore12/json-weather-prediction.png?branch=master)](https://travis-ci.org/DMoore12/json-weather-prediction)

---

**Project Timeline:**

- [x] Project is buildable
- [x] Project can load .json files
- [x] Project can parse .json files for use
- [ ] Project works as advertised
- [x] Setup Travis
- [ ] Documentation provided

json-weather-prediction is an application that will intake a .json file and output probability of a thunderstorm based on the data inside. It will be designed for use on a Raspberry Pi terminal, but will hopefully be available for more than just this use. It's initial production was designed for use with the [HyperStation.](https://github.com/russelltg/weatherstation) However, this project does not actually save .json files, so future implementation might shift away from reading .json files.

The .json file, `weatherData.json`, is contained in the same directory as the executable and follows the format of the [HyperStation project.](https://github.com/russelltg/weatherstation) This format is as follows:

```JSON
{"sensor" : "wind" , "reading" : 5}
{"sensor" : "temp" , "reading" : 20}
{"sensor" : "humidity" , "reading" : 60}
```

This format assumes wind data is in km/hr, temperature data is in degrees C, and humidity is a percentage.

The project does not use a standard .json parser, so it cannot accept *any* data. All data must be in the format above. However, the project should be able to accept other data types. It will just ignore these as they aren't useful for the [HyperStation.](https://github.com/russelltg/weatherstation)

Travis ci can be found [here.](https://travis-ci.org/DMoore12/json-weather-prediction#)
