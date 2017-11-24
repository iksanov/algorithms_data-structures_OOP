#include "Solver.h"
#include <fstream>

int main() {
  std::ifstream fin("input.txt");
  std::ofstream fout("output.txt");
  Solver tree_analyzer;
  tree_analyzer.input(fin);
  tree_analyzer.run();
  tree_analyzer.output_height_difference(fout);
  tree_analyzer.output_width_difference(fout);
  fin.close();
  fout.close();
  return 0;
}
