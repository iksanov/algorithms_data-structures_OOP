#include "Solver.h"
#include "Treap.h"
#include "BST.h"

void Solver::input(std::istream& in) {
  in >> num_of_pairs;
  for (int i = 0; i < num_of_pairs; ++i) {
    int key, prior;
    in >> key >> prior;
    pairs.push_back(std::make_pair(key, prior));
  }
}

void Solver::run() {
  Treap cartesian_tree;
  BST binary_search_tree;
  for (int i = 0; i < num_of_pairs; ++i) {
    cartesian_tree.insert(pairs[i].first, pairs[i].second);
    binary_search_tree.insert(pairs[i].first);
  }
  treap_height = cartesian_tree.get_height();
  bst_height = binary_search_tree.get_height();
  treap_max_width = cartesian_tree.get_max_width();
  bst_max_width = binary_search_tree.get_max_width();
}

void Solver::output_height_difference(std::ostream& out) const {
  out << (bst_height - treap_height) << std::endl;
}

void Solver::output_width_difference(std::ostream& out) const {
  out << (treap_max_width - bst_max_width);
}
