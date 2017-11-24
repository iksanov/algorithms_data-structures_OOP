#pragma once

#include <vector>

const int n = 3;

enum class Destination { U, R, D, L, NotDef }; //UP, RIGHT, DOWN, LEFT, Not Defined

using Table = std::vector<std::vector<int>>;

struct Coord
{
  Coord() {}
  Coord(int _h, int _w) : h(_h), w(_w) {}
  int h = 0;
  int w = 0;
};

class State {
public:
  State() {}
  explicit State(Table _table, Destination _from_prev = Destination::NotDef) : table(_table), from_prev(_from_prev) {}
  bool operator <(const State& other) const { return (table < other.table); }
  bool operator !=(const State& other) const { return (table != other.table); }
  std::vector<State> get_neighbors() const;
  const Table& get_table() const;
  char get_destination_letter() const;
private:
  Table table;
  Destination from_prev = Destination::NotDef;
  Coord null_pos() const;
};
