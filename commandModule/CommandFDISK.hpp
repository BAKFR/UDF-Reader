#pragma once

#include "Command.hpp"
#include "FileSystemTree.hpp"

class CommandFDISK : public Command {
public:
  virtual bool execute(FileSystemTree &tree);
};
