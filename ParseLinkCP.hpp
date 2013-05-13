#pragma once

#include <string>
#include "Command.hpp"
#include "ParseLink.hpp"

class ParseLinkCP : public ParseLink
{
public:
  virtual bool test(std::string stringCommand);
  virtual Command *parse(std::string stringCommand);
};
