#include "Solver.h"
#include <fstream>

int main() {
  std::ifstream fin("input.txt");
  std::ofstream fout("output.txt");
  Solver second_statistics_finder;
  second_statistics_finder.input(fin);
  second_statistics_finder.run();
  second_statistics_finder.output(fout);
  fin.close();
  fout.close();
  return 0;
}
