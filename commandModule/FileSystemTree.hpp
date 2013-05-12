#pragma once

#include <string>
#include "Node.hpp"
#include "UDF.hpp"

class FileSystemTree
{
protected:
  Node *root;
  Node *workingDirectory;
public:
  FileSystemTree();
  void buildFromUDF(UDF &udf);
  Node *getRoot();
  void setRoot(Node *node);
  Node *getWorkingDirectory();
  void setWorkingDirectory(Node *node);
  Node *getNode(std::string path);
};
