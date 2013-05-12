#include "Node.hpp"

Node::Node() {
  this->data = NULL;
}

Node *Node::getParentNode() {
  return parent;
}

std::vector<Node *> &Node::getChildNodes() {
  return nodeChilds;
}

void Node::setParentNode(Node *parent) {
  this->parent = parent;
}

void Node::setChildNodes(std::vector<Node *> nodeChilds) {
  this->nodeChilds = nodeChilds;
}

void Node::addChild(Node *child) {
  this->nodeChilds.push_back(child);
}

void Node::setNodeInformation(NodeInformation *info) {
  this->data = info;
}

NodeInformation *Node::getNodeInformation() {
  return data;
}
