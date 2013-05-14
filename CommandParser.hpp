#pragma once

#include <string>
#include "UDF.hpp"
#include "ParseLink.hpp"
#include "FileSystem.hpp"
#include "Command.hpp"

class CommandParser
{
protected:
  ParseLink *chainOfResponsibility;
public:
  CommandParser();
  Command* parse(std::string commandString);
  bool execute(FileSystem &tree, Command *command, UDF* udf);
};
