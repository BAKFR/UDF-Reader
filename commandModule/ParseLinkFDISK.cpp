#include <sstream>
#include "ParseLinkFDISK.hpp"
#include "CommandFDISK.hpp"

bool ParseLinkFDISK::test(std::string stringCommand) {
  std::stringstream parser(stringCommand);
  std::string token;

  if (parser>>token) {
    if (token == "FDISK" || token == "fdisk") {
      return true;
    }
  }
  else {
    return false;
  }
}

Command *ParseLinkFDISK::parse(std::string stringCommand) {
  return new CommandFDISK;
}
