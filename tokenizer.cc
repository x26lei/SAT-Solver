#include "tokenizer.h"
#include<vector>
#include<sstream>
using namespace std;
#include<iostream>

Tokenizer::Tokenizer(std::string ln) {
  // complete the constructor
  // vector<string> token;
  // sregex_token_iterator it{in.begin()}
  this->indexInput = 0;
  this->input = ln;
  // std::cout << ln << std::endl;
  this->hasTokenFlag = false;
  this->advanceToken();
}

bool Tokenizer::isLetter(char ch) {
  if ((ch <= 'z' && ch >= 'a')||(ch <= 'Z' && ch >= 'A')){
    return true;
    }
  return false;
}

bool Tokenizer::isNumber(char ch) {
  if (ch <= '9' && ch >= '0'){
    return true;
    }
  return false;
}

bool Tokenizer::advanceToken() {
  // your code starts here
  State state = BEGIN;
  string tokenBuild;
  if (indexInput == input.length()){
    state = END;}
  // std::cout << input << std::endl;
  while (indexInput < input.length()) {
    char ch = input[indexInput];
    indexInput = indexInput + 1;
    if (!(isLetter(ch) || isNumber(ch) || (ch==' ')  ||(ch=='\0') || (ch==';')|| (ch==':') || 
    (ch=='+') || (ch==',') || (ch=='-') || (ch=='*') || (ch=='(')||(ch==')'))){
      throw "Error: invalid input";
     }

    if (state == BEGIN){
      if (ch == ' '){
        if (indexInput == input.length()){
          state = END;
        }
      }
      else if (isLetter(ch) || isNumber(ch)){
        token.type = "variable";
        state = CONTINUE;
        tokenBuild = tokenBuild + ch;
      }
      // else if ((ch=='1')||(ch=='0')){
      //   token.type = "constant";
      //   state = FINISH;
      // }
      else if ((ch==';')||(ch==':')||(ch==',')){
        token.type = "punctuation";
        state = FINISH;
      }
      else if ((ch=='+')||(ch=='-')||(ch=='*')||(ch=='(')||(ch==')')){
        token.type = "operator";
        state = FINISH;
      }
    }
    else if (state == CONTINUE){
      if (!isLetter(ch)  && !isNumber(ch)){
        indexInput = indexInput - 1;
        // std::cout << "hello" << std::endl;
        state = FINISH;
        if ((tokenBuild.length() == 1)){
          if ((tokenBuild == "0") || (tokenBuild == "1")){
            token.type = "constant";
            }
        }
        // std::cout << "tokenlength:" << tokenBuild.length() << std::endl;
        else if (isNumber(tokenBuild[0]) || (tokenBuild.length() >= 10)){
          // std::cout << tokenBuild[0] << std::endl;
          // std::cout << "Error: invalid input" << std::endl;
          throw "Error: invalid input";
        }
        break;
      }
      tokenBuild = tokenBuild + ch;
    }
    
    if (state == CONTINUE){
      if (tokenBuild.length() == 1){
        if ((tokenBuild == "0") || (tokenBuild == "1")){
          token.type = "constant";
        }
      }
    }

    if (state == FINISH){
      tokenBuild = tokenBuild + ch;
      
      break;
    }
  }
  if (state == END){
    hasTokenFlag = false;
    return false;
  }
  token.content = tokenBuild;
  hasTokenFlag = true;
  if ((tokenBuild.length() == 1)){
      if ((tokenBuild == "0") || (tokenBuild == "1")){
        token.type = "constant";
        }
    }
    // std::cout << "tokenlength:" << tokenBuild.length() << std::endl;
    else if (isNumber(tokenBuild[0]) || (tokenBuild.length() >= 10)){
      // std::cout << tokenBuild[0] << std::endl;
      // std::cout << "Error: invalid input" << std::endl;
      throw "Error: invalid input";
    }
  return true;
}

bool Tokenizer::hasToken() const {
  // your code starts here
  // if (indexInput != input.length()){
  if (hasTokenFlag == true){
    return true;
  }
  return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  // Token resultToken;
  // your code starts there
  
  // return resultToken;
  return token;
}
