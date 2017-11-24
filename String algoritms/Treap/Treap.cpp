#include "Treap.h"
#include <queue>
#include <algorithm>

Treap::~Treap() {
  std::queue<TreapNode*> q;
  if (root == nullptr) {
    return;
  }
  q.push(root);
  while (!q.empty()) {
    TreapNode* cur_node = q.front();
    q.pop();
    if (cur_node->right != nullptr) {
      q.push(cur_node->right);
    }
    if (cur_node->left != nullptr) {
      q.push(cur_node->left);
    }
    delete cur_node;
  }
}

void Treap::split(TreapNode* current_node, int key, TreapNode*& left, TreapNode*& right) const {
  if (current_node == nullptr) {
    left = nullptr;
    right = nullptr;
    return;
  }
  if (current_node->key < key) {
    split(current_node->right, key, current_node->right, right);
    left = current_node;
  }
  else {
    split(current_node->left, key, left, current_node->left);
    right = current_node;
  }
}

void Treap::merge(TreapNode*& current_node, TreapNode* left, TreapNode* right) {
  if (left == nullptr) {
    current_node = right;
  }
  if (right == nullptr) {
    current_node = left;
  }
  if (left->priority > right->priority) {
    merge(left->right, left->right, right);
    current_node = left;
  }
  else {
    merge(right->left, left, right->left);
    current_node = right;
  }
}

void Treap::insert_node(TreapNode*& current_node, TreapNode* new_node) {
  if (current_node == nullptr) {
    current_node = new_node;
    return;
  }
  if (current_node->priority > new_node->priority) {
    if (new_node->key < current_node->key) {
      insert_node(current_node->left, new_node);
    }
    else {
      insert_node(current_node->right, new_node);
    }
  }
  else {
    split(current_node, new_node->key, new_node->left, new_node->right);
    current_node = new_node;
  }
}

void Treap::insert(int key, int priority) {
  insert_node(root, new TreapNode(key, priority));
}

int Treap::height(TreapNode* current_node, int height_) const {
  if (current_node == nullptr) {
    return height_;
  }
  return std::max(height(current_node->left, height_ + 1), height(current_node->right, height_ + 1));
}

int Treap::get_height() const {
  return height(root, 0);
}

int Treap::get_max_width() const {
  int max_width = 0;
  int curr_width = 0;
  if (root == nullptr) {
    return  0;
  }
  std::queue<TreapNode*> q;
  q.push(root);
  q.push(nullptr); //separator
  while (!q.empty()) { // == true
    TreapNode* node = q.front();
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
