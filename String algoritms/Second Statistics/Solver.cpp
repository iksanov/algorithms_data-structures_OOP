#include "Solver.h"
#include "SegmentTree.h"

int Solver::return_len_of_2_degree(int size) {
  int new_size = 1;
  while (new_size < size) {
    new_size *= 2;
  }
  return new_size;
}

void Solver::input(std::istream& in) {
  in >> array_size >> num_of_ranges;
  array_size_of_2_degree = return_len_of_2_degree(array_size);
  array.resize(array_size_of_2_degree);
  for (int i = 0; i < array_size; ++i) {
    in >> array[i];
  }
  vec_of_ranges.resize(num_of_ranges);
  for (int i = 0; i < num_of_ranges; ++i) {
    int begin;
    int end;
    in >> begin >> end;
    vec_of_ranges[i] = std::make_pair(begin, end);
  }
}

void Solver::run() {
  for (int i = array_size; i < array_size_of_2_degree; ++i) {
    array[i] = INF;
  }
  SegmentTree rmq(array);
  rmq.tree_build(0, 0, array_size_of_2_degree);
  answer.resize(num_of_ranges);
  for (int i = 0; i < num_of_ranges; ++i) {
    answer[i] = rmq.get_min(0, 0, array_size_of_2_degree - 1, vec_of_ranges[i].first - 1, vec_of_ranges[i].second - 1).second;
  }
}

void Solver::output(std::ostream& out) {
  for (int i = 0; i < num_of_ranges; ++i) {
    out << answer[i] << std::endl;
  }
}
