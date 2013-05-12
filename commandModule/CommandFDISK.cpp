#include <iostream>
#include "CommandFDISK.hpp"

bool CommandFDISK::execute(FileSystemTree &tree) {
  std::cout<<"Command FDISK executed."<<std::endl;
  return true;
}
