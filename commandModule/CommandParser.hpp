#pragma once

#include <string>
#include "ParseLink.hpp"
#include "FileSystemTree.hpp"
#include "Command.hpp"

class CommandParser
{
protected:
  ParseLink *chainOfResponsibility;
public:
  CommandParser();
  Command* parse(std::string commandString);
  bool execute(FileSystemTree &tree, Command &command);
};
