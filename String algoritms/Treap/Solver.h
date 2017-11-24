#pragma once
#include <vector>
#include <iostream>

class Solver {
public:
  void input(std::istream& in);
  void run();
  void output_height_difference(std::ostream& out) const;
  void output_width_difference(std::ostream& out) const;
private:
  int num_of_pairs = 0;
  std::vector<std::pair<int, int>> pairs;
  int treap_height = 0;
  int bst_height = 0;
  int treap_max_width = 0;
  int bst_max_width = 0;
};
