#include "SegmentTree.h"
#include <algorithm>

void SegmentTree::tree_build(int curr_node_index, int l, int r) {
  if (l == r) {
    return;
  }
  if (r - l == 1) {
    tree[curr_node_index].first = array[l];
    tree[curr_node_index].second = INF;
  }
  else {
    int m = (l + r) / 2;
    tree_build(2 * curr_node_index + 1, l, m);
    tree_build(2 * curr_node_index + 2, m, r);
    tree[curr_node_index].first = std::min(tree[2 * curr_node_index + 1].first, tree[2 * curr_node_index + 2].first);
    tree[curr_node_index].second = std::min(std::max(tree[2 * curr_node_index + 1].first, tree[2 * curr_node_index + 2].first),
      std::min(tree[2 * curr_node_index + 1].second, tree[2 * curr_node_index + 2].second));
  }
}

std::pair<int, int> SegmentTree::get_min(int curr_node_index, int tl, int tr, int l, int r) {
  if (l > r)
    return std::make_pair(INF, INF);
  if (l == tl && r == tr)
    return tree[curr_node_index];
  int tm = (tl + tr) / 2;
  std::pair<int, int> left_son_min = get_min(curr_node_index * 2 + 1, tl, tm, l, std::min(r, tm));
  std::pair<int, int> right_son_min = get_min(curr_node_index * 2 + 2, tm + 1, tr, std::max(l, tm + 1), r);
  std::pair<int, int> result = std::make_pair(std::min(left_son_min.first, right_son_min.first),
    std::min(std::max(left_son_min.first, right_son_min.first), std::min(left_son_min.second, right_son_min.second)));
  return result;
}
