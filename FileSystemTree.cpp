#include "FileSystemTree.hpp"

FileSystemTree::FileSystemTree() {
  root = NULL;
  workingDirectory = NULL;
}

void FileSystemTree::buildFromUDF(UDF &udf) {
}

Node *FileSystemTree::getRoot() {
  return root;
}

Node *FileSystemTree::getWorkingDirectory() {
  return workingDirectory;
}

Node *FileSystemTree::getNode(std::string path) {
  return NULL;
}
