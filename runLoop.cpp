#include <iostream>
#include <string>

std::string path = "/";

void runLoop() {
  std::cout << "RUNNING. . ." << std::endl;
  std::cout << "Enter the path of the 'weatherData.json' file:" << std::endl;
  std::cin >> path;
  
}
