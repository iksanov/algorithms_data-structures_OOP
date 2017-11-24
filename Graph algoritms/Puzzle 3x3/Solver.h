#pragma once

#include "State.h"

#include <map>
#include <vector>

using Table = std::vector<std::vector<int>>;

class Solver {
public:
  void input(std::istream& in);
  void output(std::ostream& out);
  void run();
private:
  std::map<State, State> previous;
  State start_state;
  Table target_table;
  bool if_solution_exists = false;
  void target_table_init();
  State target_state;
  State bfs(); //returns if there is a soltion or not
  bool check_if_solution_exists() const;
  int ans_num = 0;
  std::string ans_str = "";
};
