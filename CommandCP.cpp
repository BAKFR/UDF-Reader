#include "UDF.hpp"
#include <iostream>
#include "CommandCP.hpp"
#include "FileSystem.hpp"

bool CommandCP::execute(FileSystem &tree, UDF& udf) {
  (void)tree;
  (void)udf;
  std::cout<<"Command CP executed."<<std::endl;
  return true;
}
