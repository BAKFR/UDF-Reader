#pragma once
#include "FileSystemTree.hpp"

enum CommandType {
  COMMAND_TYPE_CD = 0,
  COMMAND_TYPE_DIR,
  COMMAND_TYPE_CP,
  COMMAND_TYPE_EXIT,
  COMMAND_TYPE_FDISK
};

class Command
{
protected:
  enum CommandType type;
public:
  virtual bool execute(FileSystemTree &tree) = 0;
  virtual ~Command(){}
};
