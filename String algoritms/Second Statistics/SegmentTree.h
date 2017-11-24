#pragma once
#include <limits>
#include <vector>
#include <utility>

const int INF = std::numeric_limits<int>::max();

class SegmentTree {
public:
  SegmentTree(){}
  explicit SegmentTree(const std::vector<int>& _array) : array(_array) { tree.resize(4 * array.size(), std::make_pair(INF, INF)); }
  void tree_build(int curr_node_index, int l, int r);
  std::pair<int, int> get_min(int curr_node_index, int tl, int tr, int l, int r);
private:
  const std::vector<int> array;
  std::vector < std::pair<int, int> > tree;
};
