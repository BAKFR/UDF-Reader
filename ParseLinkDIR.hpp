#pragma once

#include "ParseLink.hpp"
#include "Command.hpp"
#include <string>

class ParseLinkDIR : public ParseLink {
public:
  virtual bool test(std::string stringCommand);
  virtual Command *parse(std::string stringCommand);
};
