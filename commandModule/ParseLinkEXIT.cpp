#include <sstream>
#include "CommandEXIT.hpp"
#include "ParseLinkEXIT.hpp"

bool ParseLinkEXIT::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser >> token) {
    if (token == "EXIT" || token == "exit") {
      return true;
    }
  } else {
    return false;
  }
}

Command *ParseLinkEXIT::parse(std::string stringCommand) {
  return new CommandEXIT;
}
