#include "UDF.hpp"
#include <cstdlib>
#include <iostream>
#include "CommandEXIT.hpp"

bool CommandEXIT::execute(FileSystemTree &tree, UDF &udf) {
  std::cout<<"Command exit executed."<<std::endl;
  exit(0);
  return true;
}
