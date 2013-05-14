#include "UDF.hpp"
#include <iostream>
#include "CommandCD.hpp"
#include "FileSystem.hpp"

bool CommandCD::execute(FileSystem &tree, UDF &udf) {
  (void)tree;
  (void)udf;
  std::cout<<"Command cd executed."<<std::endl;
  return true;
}
