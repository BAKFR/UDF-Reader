#include "UDF.hpp"
#include <iostream>
#include "CommandDIR.hpp"

bool CommandDIR::execute(FileSystemTree &tree, UDF& udf) {
  (void)tree;
  (void)udf;
  std::cout<<"Command dir executed."<<std::endl;
  return true;
}
