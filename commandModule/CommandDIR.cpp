#include <iostream>
#include "CommandDIR.hpp"

bool CommandDIR::execute(FileSystemTree &tree) {
  std::cout<<"Command dir executed."<<std::endl;
  return true;
}
