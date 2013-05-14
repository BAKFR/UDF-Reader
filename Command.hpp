#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "UDF.hpp"
#include "FileSystem.hpp"

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
  std::vector<std::string> arguments;
  UDF::Info *i;
public:
  void setUDFInfo(UDF::Info *i) {
    this->i = i;
  }
  virtual bool execute(FileSystem &tree, UDF& udf) = 0;
  void addArgument(std::string argument) {
    this->arguments.push_back(argument);
  }
  unsigned int getArgumentNumber() {
    return arguments.size();
  }
  std::vector<std::string> &getArgumentList() {
    return arguments;
  }
  std::string getArgument(unsigned int i) {
    unsigned int count = 0;
    std::vector<std::string>::iterator it;

    if (i >= arguments.size()) {
      return "";
    }
    it = arguments.begin();
    while (count < i) {
      it++;
      count++;
    }
    return *it;
  }

  std::vector<std::string> splitPath(std::string path, char delimiter) {
    std::vector<std::string> result;

    std::stringstream data(path);
    std::string line;
    while (std::getline(data, line, delimiter)) {
      if (line != "") {
	result.push_back(line);
      }
    }
    return result;
  }

  virtual ~Command(){}
};
