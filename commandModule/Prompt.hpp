#pragma once

#include "FileSystemTree.hpp"
#include "Command.hpp"
#include "CommandParser.hpp"
#include "UDF.hpp"

class Prompt {
protected:
  int fd;
  UDF::Info *i;
  FileSystemTree fst;
  UDF *udf;
  CommandParser parser;
  std::string promptPath;
public:
  Prompt(int argc, char **argv);
  void displayArguments(Command *cmd);
  void run();
};
