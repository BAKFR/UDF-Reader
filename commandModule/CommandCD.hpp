#pragma once

#include "Command.hpp"
#include "FileSystemTree.hpp"

class CommandCD : public Command {
public:
  virtual bool execute(FileSystemTree &tree);
};
