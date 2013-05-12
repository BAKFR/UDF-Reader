#include "UDF.hpp"
#include <iostream>
#include "CommandFDISK.hpp"

bool CommandFDISK::execute(FileSystemTree &tree, UDF& udf) {
  std::cout<<"Command FDISK executed."<<std::endl;
  return true;
}
