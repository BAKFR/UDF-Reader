#pragma once

#include "Command.hpp"
#include "FileSystemTree.hpp"

class CommandCP : public Command {
public:
  virtual bool execute(FileSystemTree &tree);
};
