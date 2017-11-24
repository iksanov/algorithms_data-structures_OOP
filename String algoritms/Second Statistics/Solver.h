#pragma once
#include <vector>
#include <iostream>

class Solver {
public:
  void input(std::istream& in);
  void run();
  void output(std::ostream& out);
private:
  int array_size = 0;
  int num_of_ranges = 0;
  int array_size_of_2_degree = 0;
  std::vector<int> array;
  std::vector<std::pair<int, int>> vec_of_ranges;
  std::vector<int> answer;
  static int return_len_of_2_degree(int size);
};
