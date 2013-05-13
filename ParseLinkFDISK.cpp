#include <sstream>
#include <iostream>
#include "ParseLinkFDISK.hpp"
#include "CommandFDISK.hpp"

bool ParseLinkFDISK::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser>>token) {
    if (token == "FDISK" || token == "fdisk") {
      return true;
    } else {
      return false;
    }
  }
  else {
    return false;
  }
}

Command *ParseLinkFDISK::parse(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;
  int i = 0;

  while (parser >> token) {
    i++;
  }
  if (i == 1) {
    return new CommandFDISK;
  } else {
    std::cout<<"Invalid arguments for FDISK command."<<std::endl;
    return NULL;
  }
}
