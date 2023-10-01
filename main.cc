#include "tseitinTransformer.h"
#include "satSolver.h"

#include "parser.h"
#include <iostream>
#include <string>
#include <map>
#include "treeNode.h"

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF

int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    if (std::cin.eof()){
      // std::cout << "break1" <<std::endl;
      break;
    }
    try
    {
      std::string line; // store each input line
      // std::cout << "Please add a new input: ";
      getline (std::cin, line);
      bool eof = false;
      if (std::cin.eof()){
        eof = true;
      }
      if (line == "" && eof)
      {  
        // std::cout << "break2" <<std::endl;
        break; 
      }
      FormulaParser formulaPar (line);
      TreeNode *root = formulaPar.getTreeRoot();
      TseitinTransformer tseitinTransform(root);
      tseitinTransform.transform();
      std::string result = tseitinTransform.cnfString();
      // std::cout<< "output" <<std::endl;
      // std::cout<< result <<std::endl;
      bool output = satCallingMiniSat(tseitinTransform.getVarNum(), tseitinTransform.getCnf());
    }
    catch (char const* err)
    {
      std::cout << err << std::endl;
    }
  }
  return 0;
}