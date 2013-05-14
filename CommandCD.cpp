#include "UDF.hpp"
#include <iostream>
#include "CommandCD.hpp"
#include "FileSystem.hpp"

bool CommandCD::execute(FileSystem &fs, UDF &) {

  fs.move(arguments[0]);

  std::cout<<"Command cd executed."<<std::endl;
  return true;
}
