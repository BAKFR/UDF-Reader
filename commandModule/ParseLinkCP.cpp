#include <sstream>
#include <iostream>
#include "ParseLinkCP.hpp"
#include "CommandCP.hpp"

bool ParseLinkCP::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser>>token) {
    if (token == "CP" || token == "cp") {
      return true;
    } else {
      return false;
    }
  }
  else {
    return false;
  }
}

Command *ParseLinkCP::parse(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;
  std::string arg1;
  std::string arg2;
  Command *tmp;
  int i = 0;

  while (parser >> token) {
    if (i == 1) {
      arg1 = token;
    }
    if (i == 2) {
      arg2 = token;
    }
    i++;
  }
  if (i == 3) {
    tmp = new CommandCP;
    tmp->addArgument(arg1);
    tmp->addArgument(arg2);
    return tmp;
  } else {
    std::cout<<"Invalid arguments for CP command."<<std::endl;
    return NULL;
  }
}
