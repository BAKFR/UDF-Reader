#include <sstream>
#include <string>
#include <iostream>
#include "ParseLinkCD.hpp"
#include "CommandCD.hpp"

bool ParseLinkCD::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser>>token)
    {
      if (token == "CD" || token == "cd") {
	return true;
      } else {
	return false;
      }
    }
  else
    {
      return false;
    }

}

Command *ParseLinkCD::parse(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;
  std::string arg1;
  Command *tmp;
  int i = 0;

  while (parser >> token) {
    if (i == 1) {
      arg1 = token;
    }
    i++;
  }
  if (i == 2) {
    tmp = new CommandCD;
    tmp->addArgument(arg1);
    return tmp;
  } else {
    std::cout<<"Invalid arguments for CD command."<<std::endl;
    return NULL;
  }
}
