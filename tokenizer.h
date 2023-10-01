#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

struct Token
{
    std::string content;
    std::string type;
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
  private:
    std::string input;
    int indexInput;
    Token token;
    bool hasTokenFlag;
    enum State{
      BEGIN,
      CONTINUE,
      FINISH,
      END,
    };
  // your code starts here
  public:
    Tokenizer(std::string ln);
    bool advanceToken(); // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    bool isLetter(char ch);
    bool isNumber(char ch);
    Token getToken(); // returns the token being processed

};

#endif
