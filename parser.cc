#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include <iostream>
#include <exception>
// #include "tokenizer.cc"  //remove later

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
  if (tknzr->hasToken() == false){
    throw "Error: invalid input";
  }
  Token res = tknzr->getToken();
  if (!(res.type == "constant" || res.type == "variable" || res.content == "(" || res.content == "-"))
  {
    throw "Error: invalid input";
  }
  TreeNode *t1;
  TreeNode *t2;
  TreeNode *andNode1;
  t1 = parseTerm();
  // std::cout <<"conj t1:" << t1->getContent() << std::endl; 
  if (expected){
    tknzr->advanceToken();
  }
  if (tknzr->hasToken())
  {
    res = tknzr->getToken();
    if (!(res.content == "+" || res.content == "*" || res.content == ")"))
    {
      throw "Error: invalid input";
    }
    if (res.content != "*"){
      expected = false;
      return t1;
    }
    if (res.content == "*"){
      expected = true;
      tknzr->advanceToken();
      t2 = parseConjTerm();
      OperatorNode *andNode = new OperatorNode(res.content);
      andNode1 = andNode;
      andNode1->updateChildren(t1, t2);
      return andNode1;
    }
  }
  
  return t1;
}

TreeNode *FormulaParser::parseTerm() {
  // your code starts here
  TreeNode *t;
  TreeNode *negNode1;
  if (tknzr->hasToken() == false){
    throw "Error: invalid input";
  }
  Token res = tknzr->getToken();
  if (!(res.type == "constant" || res.type == "variable" || res.content == "(" || res.content == "-"))
  {
    throw "Error: invalid input";
  }
  // std::cout <<"termRes:" << res.content << std::endl; 
  if (res.content == "("){
    tknzr->advanceToken();
    t = parseFormula();       //add error check ")" here
    if (expected)
    {
      tknzr->advanceToken();
    }
    if (tknzr->getToken().content != ")")
    {
      // std::cout << "Error: expected ) but got: " << tknzr->getToken().content << std::endl;
      throw "Error: expected ) but got unexpected value";
    }
    else{
      expected = true;
    }
    return t;
  }
  if (res.content == "-"){
    tknzr->advanceToken();
    t = parseTerm();       //add error check ")" here
    OperatorNode *negNode = new OperatorNode(res.content);
    negNode1 = negNode;
    negNode1->updateLeftChild(t);
    return negNode1;
  }
  if (res.type == "constant"){
    ConstantNode *constantNode = new ConstantNode(res.content);
    t = constantNode;
    return t;
  }
  if (res.type == "variable"){
    VariableNode *variableNode = new VariableNode(res.content);
    t = variableNode;
    return t;
  }
  return nullptr;
}

TreeNode *FormulaParser::parseFormula() {
  // your code starts here
  if (tknzr->hasToken() == false){
    throw "Error: invalid input";
  }
  Token res = tknzr->getToken();
  if (!(res.type == "constant" || res.type == "variable" || res.content == "(" || res.content == "-"))
  {
    throw "Error: invalid input";
  }
  TreeNode *t1;
  TreeNode *t2;
  TreeNode *plusNode1;
  // std::cout << "formula res:"<< res.content << std::endl;
  t1 = parseConjTerm();
  // std::cout <<"formula t1" <<t1->getContent() << std::endl;
  if (expected){
    tknzr->advanceToken();
  }
  if (tknzr->hasToken())
  {
    res = tknzr->getToken();
    if (!(res.content == "+" || res.content == "*" || res.content == ")"))
    {
      // std::cout << res.content << std::endl;
      throw "Error: invalid input";
    }
    // std::cout << "formula res2:"<< res.content << std::endl;
    if (res.content == "+"){
      expected = true;
      tknzr->advanceToken();
      t2 = parseFormula();
      OperatorNode *plusNode = new OperatorNode(res.content);
      plusNode1 = plusNode;
      plusNode1->updateChildren(t1, t2);
      return plusNode1;
    }
  }
  
  expected = false;
    // std::cout <<  << std::endl;
  return t1;
}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  // TreeNode *root;
  treeRoot = parseFormula();

  // std::cout <<"getTreeRoot: " <<treeRoot->getContent() << std::endl;
  return treeRoot;
}

FormulaParser::~FormulaParser() {
  // your code starts here
  delete tknzr;
  // std::cout << "formula start" <<std::endl;
  if (treeRoot != nullptr)
  {
    // std::cout << "sad" <<std::endl;
    delete treeRoot;
  }
  // std::cout << "formula end" <<std::endl;
}

AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
  std::map<std::string, bool> results;
  // your code starts here
  while (tknzr->hasToken()){
      Token res = tknzr->getToken();
      std::string var;
      bool ass;
      bool duplicateFlag = false;
      int duplicateVal;
      bool contraFlag = false;
      if  (res.type != "variable"){
        throw "Error: invalid input";
      }
      if (res.type == "variable"){
        // std::cout << "variable:" << res.content << std::endl; 
        var = res.content;
        if (results.find(var) != results.end()){
          // std::cout<< "is b:" << var <<std::endl;
          duplicateFlag = true;
          duplicateVal = results.find(var)->second;
          // std::cout << "duplicateVal:" << duplicateVal << std::endl; 
        }
        tknzr->advanceToken();
        Token res = tknzr->getToken();
        if (res.content != ":"){
          throw "Error: invalid input";
        }
        if (res.content == ":"){
          tknzr->advanceToken();
          Token res = tknzr->getToken();
          // std::cout << "constant type:" << res.type << std::endl; 
          if (res.type != "constant"){
            throw "Error: invalid input";
          }
          if (res.type == "constant"){
            // std::cout << "constant:" << res.content << std::endl; 
            // std::cout << "hi" << std::endl; 
            if (res.content == "1"){
              ass = 1;
            }
            else
            {
              ass = 0;
            }
          }
          if (duplicateFlag == true){
            if (ass != duplicateVal){
              // std::cout << "ass:" << ass << std::endl; 
              // std::cout << "Error: contradicting assignment" << std::endl; 
              contraFlag = true;
              throw "Error: contradicting assignment";
            }
          }
        }
      }
      results[var] = ass;
      // std::cout << res.type << std::endl;
      // std::cout << "map val:" << res.content << std::endl;
      tknzr->advanceToken();
      if (tknzr->hasToken())
      {
        Token res = tknzr->getToken();
        if (res.content != ",")
        {
          throw "Error: invalid input";
        }
        tknzr->advanceToken();
        // if (tknzr->hasToken() == false)
        // {
        //   throw "Error: invalid input";
        // }
      }
  }

  return results;
}

AssignmentParser::~AssignmentParser() {
  // your code starts here
  // std::cout << "ass start" <<std::endl;
  delete tknzr;
  // std::cout << "ass end" <<std::endl;
}