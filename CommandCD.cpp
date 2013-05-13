#include "UDF.hpp"
#include <iostream>
#include "CommandCD.hpp"

bool CommandCD::execute(FileSystemTree &tree, UDF &udf) {
  (void)tree;
  (void)udf;
  std::cout<<"Command cd executed."<<std::endl;
  return true;
}
