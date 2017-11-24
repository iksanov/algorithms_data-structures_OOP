#pragma once

struct TreapNode {
  TreapNode() {}
  TreapNode(int _key, int _priority, TreapNode* _left = nullptr, TreapNode* _right = nullptr)
    : key(_key), priority(_priority), left(_left), right(_right) {}
  int key = -1;
  int priority = -1;
  TreapNode* left = nullptr;
  TreapNode* right = nullptr;
};

class Treap {
public:
  ~Treap();
  void insert(int key, int priority);
  int get_height() const;
  int get_max_width() const;
private:
  TreapNode* root = nullptr;
  void split(TreapNode* current_node, int key, TreapNode*& left, TreapNode*& right) const;
  void merge(TreapNode*& current_node, TreapNode* left, TreapNode* right);
  void insert_node(TreapNode*& current_node, TreapNode* new_node);
  int height(TreapNode* current_node, int height) const;
};
