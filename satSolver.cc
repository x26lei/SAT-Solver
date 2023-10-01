#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
// #include <iostream>
#include <memory>
#include <vector>
#include <iostream>

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> const &cnf) {
  // your code starts here 
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  std::vector<Minisat::Lit> literalList;
  for (int i = 0; i < numVar; i++){
    literalList.push_back(Minisat::mkLit(solver->newVar()));
  }
  // Minisat::Lit a = Minisat::mkLit(solver->newVar());
  for (int j = 0; j < cnf.size(); j++){
    Minisat::vec<Minisat::Lit> clause;
    for (int n = 0; n < cnf[j].size(); n++){
      if (cnf[j][n] < 0){
        // clause->addClause(literalList[-cnf[j][n]] + 1);
        int a = -cnf[j][n] - 1;
        clause.push(~literalList[a]);
      }
      if (cnf[j][n] > 0){
        int a = cnf[j][n] - 1;
        clause.push(literalList[a]);
      }
    }
    // Minisat::vec<Minisat::Lit> cnf[j];
    solver->addClause(clause);
  }

  bool res = solver->solve();
  // std::cout << "The result is: " << res << "\n";
  if (res == 0){
     std::cout << "unsat" <<std::endl;
  }
  if (res == 1){
     std::cout << "sat" <<std::endl;
  }
  return true;
}
