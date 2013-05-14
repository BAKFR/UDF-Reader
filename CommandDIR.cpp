#include "UDF.hpp"
#include <iostream>
#include "CommandDIR.hpp"
#include "FileSystem.hpp"

bool CommandDIR::execute(FileSystem &tree, UDF& udf) {
  (void)tree;
  (void)udf;
  std::cout<<"Command dir executed."<<std::endl;
  return true;
}
