#pragma once
#include <string>
#include "Command.hpp"

class ParseLink
{
public:
  ParseLink *next;
  virtual bool test(std::string stringCommand) = 0;
  virtual Command* parse(std::string stringCommand) = 0;
  virtual ~ParseLink(){};
};
