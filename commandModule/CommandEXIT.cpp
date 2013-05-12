#include <iostream>
#include "CommandEXIT.hpp"

bool CommandEXIT::execute(FileSystemTree &tree) {
  std::cout<<"Command exit executed."<<std::endl;
  return true;
}
