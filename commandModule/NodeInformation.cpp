#include "NodeInformation.hpp"

NodeInformation::NodeInformation(bool isDirectory, std::string name, std::string timestamp, unsigned long size) {
  this->isDirectory = isDirectory;
  this->name = name;
  this->timestamp = timestamp;
  this->size = size;
}
