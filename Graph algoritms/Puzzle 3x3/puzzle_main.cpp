#include "Solver.h"
#include "State.h"

#include <fstream>

int main()
{
  //std::ifstream fin("puzzle.in");
  //std::ofstream fout("puzzle.out");
  std::ifstream fin("input.txt");
  std::ofstream fout("output.txt");
  Solver puzzle_solver;
  puzzle_solver.input(fin);
  puzzle_solver.run();
  puzzle_solver.output(fout);
  fin.close();
  fout.close();
  return 0;
}
