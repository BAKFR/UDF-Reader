#pragma once

#include "FileSystemTree.hpp"
#include "Command.hpp"
#include "CommandParser.hpp"
#include "UDF.hpp"

class Prompt {
protected:
  FileSystemTree fst;
  UDF udf;
  CommandParser parser;
  std::string promptPath;
public:
  void displayArguments(Command *cmd);
  void run();
};
