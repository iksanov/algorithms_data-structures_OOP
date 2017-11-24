#include "Solver.h"
#include <fstream>

int main() {
  std::ifstream fin("input.txt");
  std::ofstream fout("output.txt");
  Solver KMPSustringsFinder;
  KMPSustringsFinder.input(fin);
  KMPSustringsFinder.run_with_output(fout);
  fin.close();
  fout.close();
  return 0;
}
