#include "../include/TouchstoneFile.h"
#include <iostream>

int main() {
  TouchstoneFile file;
  file.open("./data/example.S2P");
  std::cout << "Finished" << std::endl;
}
