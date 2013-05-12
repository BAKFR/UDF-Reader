#pragma once

#include "Command.hpp"
#include "FileSystemTree.hpp"

class CommandEXIT : public Command {
public:
  virtual bool execute(FileSystemTree &tree);
};
