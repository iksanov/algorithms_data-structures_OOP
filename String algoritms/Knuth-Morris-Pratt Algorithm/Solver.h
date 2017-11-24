#pragma once
#include <vector>
#include <istream>

class Solver {
public:
  void input(std::istream& in);
  void run_with_output(std::ostream& out);
private:
  std::string pattern;
  std::string text;
  std::vector<int> prefix_function_values;
};
