#include <sstream>
#include <iostream>
#include "CommandEXIT.hpp"
#include "ParseLinkEXIT.hpp"

bool ParseLinkEXIT::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser >> token) {
    if (token == "EXIT" || token == "exit") {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

Command *ParseLinkEXIT::parse(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;
  int i = 0;

  while (parser >> token) {
    i++;
  }
  if (i == 1) {
    return new CommandEXIT;
  } else {
    std::cout<<"Invalid arguments for EXIT command."<<std::endl;
    return NULL;
  }
}
