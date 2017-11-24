#include "State.h"

const Table& State::get_table() const {
  return table;
}

char State::get_destination_letter() const {
  switch (from_prev) {
  case Destination::U: { return 'U'; }
  case Destination::R: { return 'R'; }
  case Destination::D: { return 'D'; }
  case Destination::L: { return 'L'; }
  default: { return '$'; }
  }
}

Coord State::null_pos() const {
  for (int h = 0; h < n; ++h) {
    for (int w = 0; w < n; ++w) {
      if (this->get_table()[h][w] == 0) {
        return{ h, w };
      }
    }
  }
  return Coord();
}

std::vector<State> State::get_neighbors() const {
  std::vector<State> neighbours;
  Coord np = null_pos();
  if (np.w - 1 >= 0) {
    Table new_table = table;
    std::swap(new_table[np.h][np.w - 1], new_table[np.h][np.w]);
    State left_neighb(new_table, Destination::L);
    neighbours.push_back(left_neighb);
  }
  if (np.h - 1 >= 0) {
    Table new_table = table;
    std::swap(new_table[np.h - 1][np.w], new_table[np.h][np.w]);
    State up_neighb(new_table, Destination::U);
    neighbours.push_back(up_neighb);
  }
  if (np.w + 1 < n) {
    Table new_table = table;
    std::swap(new_table[np.h][np.w + 1], new_table[np.h][np.w]);
    State right_neighb(new_table, Destination::R);
    neighbours.push_back(right_neighb);
  }
  if (np.h + 1 < n) {
    Table new_table = table;
    std::swap(new_table[np.h + 1][np.w], new_table[np.h][np.w]);
    State down_neighb(new_table, Destination::D);
    neighbours.push_back(down_neighb);
  }
  return neighbours;
}
