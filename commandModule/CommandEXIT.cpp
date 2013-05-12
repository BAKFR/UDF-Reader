#include <cstdlib>
#include <iostream>
#include "CommandEXIT.hpp"

bool CommandEXIT::execute(FileSystemTree &tree) {
  std::cout<<"Command exit executed."<<std::endl;
  exit(0);
  return true;
}
