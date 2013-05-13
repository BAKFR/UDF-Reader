#pragma once

#include <vector>
#include "NodeInformation.hpp"

class Node {
protected:
  std::vector<Node *> nodeChilds;
  Node *parent;
  NodeInformation *data;
public:
  Node();
  Node *getParentNode();
  std::vector<Node *> &getChildNodes();
  void setParentNode(Node *parent);
  void setChildNodes(std::vector<Node *> nodeChilds);
  void setNodeInformation(NodeInformation *data);
  void addChild(Node *child);
  NodeInformation* getNodeInformation();
};
