#pragma once

#include <string>

class NodeInformation {
public:
  bool isDirectory;
  std::string name;
  std::string timestamp;
  unsigned long size;
  NodeInformation(bool isDirectory, std::string name, std::string timestamp, unsigned long size);
};
