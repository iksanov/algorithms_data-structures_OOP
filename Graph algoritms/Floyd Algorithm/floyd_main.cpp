#include "floyd.h"

int main()
{
  ifstream in("input.txt");
  ofstream out("output.txt");
  Solver solver;
  solver.input(in);
  solver.run();
  solver.output(out);
  in.close();
  out.close();
  return 0;
}
