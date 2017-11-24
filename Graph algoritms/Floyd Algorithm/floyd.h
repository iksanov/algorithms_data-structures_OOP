#pragma once

#include <fstream>
#include <vector>
#include <algorithm>
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using std::min;

class Solver {
public:
  void run();
  void input(istream& in);
  void output(ostream& out);
private:
  int size;
  vector<vector<int>> matrix;
};

void floyd(int size, vector<vector<int>>& matrix);
