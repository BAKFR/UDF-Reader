#include "UDF.hpp"
#include <iostream>
#include "CommandDIR.hpp"

bool CommandDIR::execute(FileSystemTree &tree, UDF& udf) {
  std::cout<<"Command dir executed."<<std::endl;
  return true;
}
