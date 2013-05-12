#include <sstream>
#include <string>
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
  return new CommandCD;
}
