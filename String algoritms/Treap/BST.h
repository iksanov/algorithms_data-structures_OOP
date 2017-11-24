#pragma once

struct BSTNode {
  BSTNode() {}
  explicit BSTNode(int _key) : key(_key), left(nullptr), right(nullptr) {}
  int key = 0;
  BSTNode* left = nullptr;
  BSTNode* right = nullptr;
};

class BST {
public:
  void insert(int key);
  int get_height() const;
  int get_max_width() const;
private:
  BSTNode* root = nullptr;
  BSTNode* recursive_insert(BSTNode* node, int key);
  int height(BSTNode* node) const;
};
