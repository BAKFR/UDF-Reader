#include <string>
#include <sstream>
#include <iostream>
#include "CommandDIR.hpp"
#include "ParseLinkDIR.hpp"

bool ParseLinkDIR::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser>>token) {
    if (token == "DIR" || token == "dir") {
      return true;
    } else {
      return false;
    }
  }
  else {
    return false;
  } 
}

Command *ParseLinkDIR::parse(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;
  int i = 0;

  while (parser >> token) {
    i++;
  }
  if (i == 1) {
    return new CommandDIR;
  } else {
    std::cout<<"Invalid argument for DIR command."<<std::endl;
  }
}

