#include <iostream>
#include "CommandCP.hpp"

bool CommandCP::execute(FileSystemTree &tree) {
  std::cout<<"Command CP executed."<<std::endl;
  return true;
}
