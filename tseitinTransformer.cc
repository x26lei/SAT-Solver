#include "tseitinTransformer.h"
#include <sstream>

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  if (subRoot != nullptr){
    if ((subRoot->getContent() == "+") || (subRoot->getContent() == "*") || (subRoot->getContent() == "-")){
      subRoot->name = "f" + std::to_string(varIdCounter);}
    else {
      subRoot->name = subRoot->getContent();
      }
    if (varIdTable.find(subRoot->name) != varIdTable.end()){
      subRoot->id = varIdTable[subRoot->name];
    }
    else{
      subRoot->id = varIdCounter;
      varIdTable[subRoot->name] = subRoot->id;
      varIdCounter++;
    }
    if (subRoot->getLeftChild() != nullptr){
      transSubformula(subRoot->getLeftChild());
    }
    if (subRoot->getRightChild() != nullptr){
      transSubformula(subRoot->getRightChild());
    }
    if (subRoot->getContent() == "+"){
      addOrEq(subRoot->id, subRoot->getLeftChild()->id, subRoot->getRightChild()->id);
    }
    if (subRoot->getContent() == "*"){
      addAndEq(subRoot->id, subRoot->getLeftChild()->id, subRoot->getRightChild()->id);
    }
    if (subRoot->getContent() == "-"){
      if (subRoot->getLeftChild() != nullptr){
        addNegEq(subRoot->id, subRoot->getLeftChild()->id);
      }
      else {
        addNegEq(subRoot->id, subRoot->getRightChild()->id);
      }
    }
  }
  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  cnf.push_back({-curID, -childID});
  cnf.push_back({curID, childID});
  // cnf.push_back({curID});
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back({-curID, leftID, rightID});
  cnf.push_back({-leftID, curID});
  cnf.push_back({-rightID, curID});
  // cnf.push_back({curID});
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back({-curID,leftID});
  cnf.push_back({-curID,rightID});
  cnf.push_back({-leftID, -rightID, curID});
  // cnf.push_back({curID});
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  transSubformula(formulaRoot);
  cnf.push_back({formulaRoot->id});
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  std::stringstream ss;
  for (int i = 0; i < cnf.size(); i++){
    ss << "[";
    for (auto it = cnf[i].begin(); it != cnf[i].end(); it++)    {
        if (it != cnf[i].begin()) {
            ss << " ";
        }
        ss << *it;  
    }
    ss << "]";
  }
  result = ss.str();
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter;
}

std::vector<std::vector<int>> TseitinTransformer::getCnf() const{
  return cnf;
}