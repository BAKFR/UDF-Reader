#include <iostream>
#include "CommandCD.hpp"

bool CommandCD::execute(FileSystemTree &tree) {
  std::cout<<"Command cd executed."<<std::endl;
  return true;
}
