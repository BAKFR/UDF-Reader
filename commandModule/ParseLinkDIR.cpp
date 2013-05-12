#include <string>
#include <sstream>
#include "CommandDIR.hpp"
#include "ParseLinkDIR.hpp"

bool ParseLinkDIR::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser>>token) {
    if (token == "DIR" || token == "dir") {
      return true;
    }
  }
  else {
    return false;
  } 
}

Command *ParseLinkDIR::parse(std::string stringCommand) {
  return new CommandDIR;
}

