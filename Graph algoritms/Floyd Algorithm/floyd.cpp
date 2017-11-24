#include "floyd.h"

void floyd(int size, vector<vector<int>>& matrix)
{
  for (int k = 0; k < size; ++k) {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
}

void Solver::run() {
  floyd(size, matrix);
}

void Solver::input(istream& in) {
  in >> size;
  matrix.resize(size, vector<int>());
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      int num;
      in >> num;
      matrix[i].push_back(num);
    }
  }
}

void Solver::output(ostream& out) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      out << matrix[i][j];
      if (j != size - 1) {
        out << " ";
      }
    }
    out << endl;
  }
}
