CXX = g++
CXXFLAGS = -Wall -g
CLEAN = main/jsonWeatherPrediction
all: cleanall jsonWeatherPrediction cleanout
cleanall:
	-rm -f $(CLEAN) main/*.o

cleanout:
	-rm -f main/*.o

jsonWeatherPrediction: main/main.o main/jsonParse.o main/jsonImport.o main/runLoop.o
	$(CXX) $(CXXFLAGS) -o main/jsonWeatherPrediction main/main.o main/jsonParse.o main/jsonImport.o main/runLoop.o

main.o: main/jsonParse.cpp main/jsonImport.cpp main/runLoop.cpp main/jsonParse.h main/jsonImport.h

jsonParse.o: main/jsonParse.h

jsonImport.o: main/jsonImport.h

runLoop.o: main/jsonParse.h main/jsonImport.h
