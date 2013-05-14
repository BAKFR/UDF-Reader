#include "UDF.hpp"
#include <cstdlib>
#include <iostream>
#include "CommandEXIT.hpp"
#include "FileSystem.hpp"

bool CommandEXIT::execute(FileSystem &tree, UDF &udf) {
  (void)tree;
  (void)udf;
  std::cout<<"Command exit executed."<<std::endl;
  exit(0);
  return true;
}
