#pragma once

#include "FileSystem.hpp"
#include "Command.hpp"
#include "CommandParser.hpp"
#include "UDF.hpp"
#include "FileSystem.hpp"

class Prompt {
protected:
  int fd;
  FileSystem *fs;
  UDF::Info *i;
  UDF *udf;
  CommandParser parser;
  std::string promptPath;
public:
  Prompt(int argc, char **argv);
  void displayArguments(Command *cmd);
  void run();
};
