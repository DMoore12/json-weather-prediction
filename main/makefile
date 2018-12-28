CXX = g++
CXXFLAGS = -Wall -g
CLEAN = jsonWeatherPrediction
all: cleanall jsonWeatherPrediction cleano
cleanall:
	-rm -f $(CLEAN) *.o

cleano:
	-rm -f *.o

jsonWeatherPrediction: main.o jsonParse.o jsonImport.o runLoop.o
	$(CXX) $(CXXFLAGS) -o jsonWeatherPrediction main.o jsonParse.o jsonImport.o runLoop.o

main.o: jsonParse.cpp jsonImport.cpp runLoop.cpp jsonParse.h jsonImport.h

jsonParse.o: jsonParse.h

jsonImport.o: jsonImport.h

runLoop.o: jsonParse.h jsonImport.h
