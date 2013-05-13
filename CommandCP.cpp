#include "UDF.hpp"
#include <iostream>
#include "CommandCP.hpp"

bool CommandCP::execute(FileSystemTree &tree, UDF& udf) {
  std::cout<<"Command CP executed."<<std::endl;
  return true;
}
