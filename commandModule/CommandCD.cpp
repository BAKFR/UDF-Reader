#include "UDF.hpp"
#include <iostream>
#include "CommandCD.hpp"

bool CommandCD::execute(FileSystemTree &tree, UDF &udf) {
  std::cout<<"Command cd executed."<<std::endl;
  return true;
}
