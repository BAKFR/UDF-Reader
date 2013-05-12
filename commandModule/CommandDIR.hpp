#pragma once

#include "UDF.hpp"
#include "Command.hpp"
#include "FileSystemTree.hpp"

class CommandDIR : public Command {
public:
  virtual bool execute(FileSystemTree &tree, UDF &udf);
};
