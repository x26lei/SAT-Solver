#include "treeNode.h"
#include <iostream>

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const{
  // your code starts here
  return content;
}

TreeNode *TreeNode::getLeftChild() const{
  // your code starts here
  return leftChild;
}
TreeNode *TreeNode::getRightChild() const{
  // your code starts here
  return rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  leftChild = lChild;
  rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  // if (getLeftChild() == NULL && getRightChild() == NULL){
  //   int curr_val = getContent();
  //   return curr_val
  // }
  if (getContent() == "+"){
    // return recursive(getLeftChild()) || recursive(getRightChild());}
    bool left_result = getLeftChild()->evaluate(assignment);
    bool right_result = getRightChild()->evaluate(assignment);
    return left_result || right_result;}
  if (getContent() == "*"){
    bool left_result = getLeftChild()->evaluate(assignment);
    bool right_result = getRightChild()->evaluate(assignment);
    return left_result && right_result;}
  if (getContent() == "-"){
    return !getLeftChild()->evaluate(assignment);}
  return false;
  // }
  // return curr_val
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (getContent() == "1"){
    return true;
  }
  if (getContent() == "0"){
    return false;
  }
  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (assignment.find(getContent()) == assignment.end()){
      // std::cout << "Error: incomplete assignment" <<std::endl;
      throw "Error: incomplete assignment";
  }
  return assignment.at(getContent());
  // return false;
}

TreeNode::~TreeNode() {
  // your code starts here
  // std::cout << "tree start" <<std::endl;
  if (leftChild != nullptr){
    delete leftChild;
  }
  if (rightChild != nullptr){
    delete rightChild;
  }
  // std::cout << "tree end" <<std::endl;
}
