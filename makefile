CXX = g++
CXXFLAGS = -Wall -g
CLEAN = main/jsonWeatherPrediction
all: cleanall jsonWeatherPrediction cleanout
cleanall:
	-rm -f $(CLEAN) main/*.o

cleanout:
	-rm -f main/*.o

jsonWeatherPrediction: main/main.o main/jsonParse.o main/jsonImport.o main/runLoop.o main/statistics.o main/algorithm.cpp
	$(CXX) $(CXXFLAGS) -o main/jsonWeatherPrediction main/main.o main/jsonParse.o main/jsonImport.o main/runLoop.o main/statistics.o main/algorithm.cpp

main.o: main/jsonParse.cpp main/jsonImport.cpp main/runLoop.cpp main/jsonParse.h main/jsonImport.h main/statistics.cpp main/algorithm.cpp

jsonParse.o: main/jsonParse.h

jsonImport.o: main/jsonImport.h

runLoop.o: main/jsonParse.h main/jsonImport.h

statistics.o: main/statistics.cpp

algorithm.o: main/algorithm.cpp
