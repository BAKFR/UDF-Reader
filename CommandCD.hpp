#pragma once

#include "UDF.hpp"
#include "Command.hpp"
#include "FileSystem.hpp"

class CommandCD : public Command {
public:
  virtual bool execute(FileSystem &tree, UDF &udf);
};
