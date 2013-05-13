#include "ParseLink.hpp"
#include "Command.hpp"
#include <string>

#pragma once

class ParseLinkCD : public ParseLink {
public:
  virtual bool test(std::string stringCommand);
  virtual Command *parse(std::string stringCommand);
};
