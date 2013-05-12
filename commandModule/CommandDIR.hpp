#pragma once

#include "Command.hpp"
#include "FileSystemTree.hpp"

class CommandDIR : public Command {
public:
  virtual bool execute(FileSystemTree &tree);
};
