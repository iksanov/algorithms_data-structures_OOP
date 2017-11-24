#include "BST.h"
#include <algorithm>
#include <queue>

BSTNode* BST::recursive_insert(BSTNode* node, int key) {
  if (node == nullptr) {
    return (new BSTNode(key));
  }
  if (key < node->key) {
    node->left = recursive_insert(node->left, key);
  }
  else if (key > node->key) {
    node->right = recursive_insert(node->right, key);
  }
  return node;
}

int BST::height(BSTNode* node) const {
  if (node == nullptr) {
    return 0;
  }
  return (std::max(height(node->left), height(node->right)) + 1);
}

void BST::insert(int key) {
  root = recursive_insert(root, key);
}

int BST::get_height() const {
  return height(root);
}

int BST::get_max_width() const {
  int max_width = 0;
  int curr_width = 0;
  if (root == nullptr) {
    return  0;
  }
  std::queue<BSTNode*> q;
  q.push(root);
  q.push(nullptr); //separator
  while (!q.empty()) { // == true
    BSTNode* node = q.front();
    q.pop();
    if (node == nullptr) {
      max_width = std::max(max_width, curr_width); //update max_width
      curr_width = 0;
      if (q.empty()) {
        break;
      }
      q.push(nullptr);
    }
    else {
      curr_width += 1;
      if (node->left != nullptr) {
        q.push(node->left);
      }
      if (node->right != nullptr) {
        q.push(node->right);
      }
    }
  }
  return max_width;
}
