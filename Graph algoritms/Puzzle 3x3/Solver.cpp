#include "Solver.h"

#include <iostream>
#include <queue>
#include <string>
#include <set>
#include <algorithm>

void Solver::target_table_init()
{
  target_table.resize(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      target_table[i][j] = (n * i + j + 1);
    }
  }
  target_table[n - 1][n - 1] = 0;
}

State Solver::bfs() {
  std::queue<State> q;
  std::set<State> used;
  q.push(start_state);
  used.insert(start_state);
  State cur;
  std::vector<State> neighbours;
  while (!q.empty() && cur.get_table() != target_table) {
    cur = q.front();
    q.pop();
    neighbours = cur.get_neighbors();
    for (int i = 0; i < int(neighbours.size()); ++i) {
      if (used.count(neighbours[i]) == 0) { //if the state hasn't been used yet
        q.push(neighbours[i]);
        used.insert(neighbours[i]);
        previous[neighbours[i]] = cur;
      }
    }
  }
  return cur;
}

bool Solver::check_if_solution_exists() const {
  int num_inversions = 0;
  std::vector<int> single_row(n*n);
  int null_line = -1;
  Table table_for_check = start_state.get_table();
  for (int i = 0; i < n; ++i) { //single_row initialisation
    for (int j = 0; j < n; ++j) {
      single_row[i*n + j] = table_for_check[i][j];
    }
  }
  for (int i = 0; i < n*n; ++i) {
    if (single_row[i] != 0) {
      for (int j = 0; j < i; ++j) {
        if (single_row[j] > single_row[i]) {
          ++num_inversions;
        }
      }
    }
    else null_line = (i / n) + 1;
  }
  int ans = num_inversions;
  if (n % 2 == 0) {
    ans = num_inversions + null_line;
  }
  return !(ans % 2);
}

void Solver::run() {
  target_table_init();
  if_solution_exists = check_if_solution_exists();
  if (if_solution_exists) {
    target_state = bfs();
  }
}

void Solver::input(std::istream& in)
{
  Table start_table(n, std::vector<int>());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int num;
      in >> num;
      start_table[i].push_back(num);
    }
  }
  start_state = State(start_table);
}

void Solver::output(std::ostream& out) {
  if (start_state.get_table() == target_table) {
    out << "0" << std::endl;
    return;
  }
  if (if_solution_exists) {
    State prev_state = target_state;
    do {
      ++ans_num;
      ans_str += prev_state.get_destination_letter();
      prev_state = previous[prev_state];
    } while (prev_state != start_state);
    reverse(ans_str.begin(), ans_str.end());
    out << ans_num << std::endl << ans_str << std::endl;
  }
  else {
    out << "-1" << std::endl;
  }
}
