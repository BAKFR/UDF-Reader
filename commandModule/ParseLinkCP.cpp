#include <sstream>
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
  return new CommandCP;
}
