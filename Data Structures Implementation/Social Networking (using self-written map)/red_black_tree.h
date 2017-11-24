#pragma once

template <typename K, typename V>
class MyMap
{
private:
	friend class Node;
	struct Node
	{
		friend class MyMap;
		K key;
		V value;
		Node(const K key_ = K(), const V value_ = V(), char color = 'R'){
			right = &NIL;
			left = &NIL;
			parent = &NIL;
			key = key_;
			value = value_;
			color = color;
		}

		Node *right;
		Node *left;
		Node *parent;

		char color;
	};

	static Node NIL;
	Node *root_;
	int size_;

	void LeftRotate(Node *x);
	void RightRotate(Node *y);
	void InsertFixUp(Node* z);
	Node *TreeSearch(const K key) const;
	void Transplant(Node *u, Node *v);
	Node *TreeMinimum(Node *x) const;
	void eraseFixup(Node *x);
	Node *TreeSuccessor(Node *x);
	void TreeDelete(Node *x);
public:
	MyMap()
	{
		root_ = &NIL;
		size_ = 0;
	}
	void Insert(const K key_, const V value_ = V());
	V &operator[](const K key);
	void erase(K key);
	bool empty() const
	{
		return size_ == 0;
	}
	int size() const
	{
		return size_;
	}
	void clear();
	void dump();
	bool exist(K key)
	{
		bool tmp;
		if (TreeSearch(key) == &NIL)
			tmp = false;
		else
			tmp = true;
		return tmp;
	}

	friend class Iterator;
	class Iterator
	{
	private:
		Node *node;
		MyMap *map;
		Iterator(MyMap *m, Node *n) : map(m), node(n) {}
		friend class MyMap;
	public:
		Iterator(const Iterator &it) : node(it.node) {}
		
		Iterator &operator++()
		{
			node = map->TreeSuccessor(node);
			return *this;
		}
		bool operator==(const Iterator &iter) const
		{
			return node == iter.node;
		}
		bool operator!=(const Iterator &iter) const
		{
			return node != iter.node;
		}
		const Node &operator*()
		{
			return *node;
		}
		const Node *operator->()
		{
			return node;
		}
	};
	Iterator begin();
	Iterator end();
};

template <typename K, typename V>
typename MyMap<K, V>::Node MyMap<K, V>::NIL(K(), V(), 'B');

template <typename K, typename V>
void MyMap<K, V>::LeftRotate(Node *x)
{
	Node *y = new Node;
	y = x->right;
	x->right = y->left;
	if (y->left != &NIL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == &NIL) {
		this->root_ = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
	delete y;
}

template <typename K, typename V>
void MyMap<K, V>::RightRotate(Node *y)
{
	Node *x = new Node;
	x = y->left;
	y->left = x->right;
	if (x->right != &NIL)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == &NIL) {
		root_ = x;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
	delete x;
}

template <typename K, typename V>
void MyMap<K, V>::Insert(const K key_, const V value_)
{
	Node* z = new Node(key_, value_, 'R');
	Node *y = &NIL;
	Node *x = root_;
	while (x != &NIL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == &NIL) {
		root_ = z;
	}
	else {
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	}
	InsertFixUp(z);
}

template <typename K, typename V>
void MyMap<K, V>::InsertFixUp(Node* z)
{
	while (z->parent->color == 'R'){
		if (z->parent == z->parent->parent->left) {
			Node *y = z->parent->parent->right;
			if (y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					LeftRotate(z);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				RightRotate(z->parent->parent);
			}
		}
		else {
			Node *y = z->parent->parent->left;
			if (y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					RightRotate(z);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				LeftRotate(z->parent->parent);
			}
		}
	}
	root_->color = 'B';
	++size_;
}

template <typename K, typename V>
typename MyMap<K, V>::Node *MyMap<K, V>::TreeSearch(const K key) const
{
	Node *x = root_;
	while (x != &NIL && key != x->key) {
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template <typename K, typename V>
V &MyMap<K, V>::operator[](const K key)
{
	Node *x = TreeSearch(key);
	if (x == &NIL) {
		Insert(key);
		x = TreeSearch(key);
	}
	return x->value;
}

template <typename K, typename V>
void MyMap<K, V>::Transplant(Node* u, Node* v)
{
	if (u->parent == &NIL)
		root_ = v;
	else
		if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
	v->parent = u->parent;
}

template <typename K, typename V>
void MyMap<K, V>::erase(K key)
{
	Node *z = TreeSearch(key);
	Node *y = z;
	char y_original_color = y->color;
	if (z == &NIL)
		return;
	Node *x;
	if (z->left == &NIL) {
		x = z->right;
		Transplant(z, z->right);
	}
	else{
		if (z->right == &NIL) {
			x = z->left;
			Transplant(z, z->left);
		}
		else{
			y = TreeMinimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else{
				Transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			Transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
	}
	if (y_original_color == 'B')
		eraseFixup(x);
	--size_;
	delete z;
}

template <typename K, typename V>
typename MyMap<K, V>::Node *MyMap<K, V>::TreeMinimum(Node *x) const
{
	while (x->left != &NIL)
		x = x->left;
	return x;
}

template <typename K, typename V>
void MyMap<K, V>::eraseFixup(Node *x)
{
	while (x != root_ && x->color == 'B') {
		if (x == x->parent->left) {
			Node *w = new Node;
			w = x->parent->right;
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 'B' && w->right->color == 'R') {
				w->color = 'R';
				x = x->parent;
			}
			else {
				if (w->right->color == 'B') {
					w->left->color = 'B';
					w->color = 'R';
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->right->color = 'B';
				LeftRotate(x->parent);
				x = root_;
			}
			delete w;
		}
		else {
			Node *w = x->parent->left;
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				RightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 'B' && w->left->color == 'R') {
				w->color = 'R';
				x = x->parent;
			}
			else {
				if (w->left->color == 'B') {
					w->right->color = 'B';
					w->color = 'R';
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->left->color = 'B';
				RightRotate(x->parent);
				x = root_;
			}
			delete w;
		}
	}
	x->color = 'B';
}

template <typename K, typename V>
typename MyMap<K, V>::Node *MyMap<K, V>::TreeSuccessor(Node *x)
{
	if (x->right != &NIL) {
		return TreeMinimum(x->right);
	}
	Node *y = x->parent;
	while (y != &NIL && x == y->right) {
		x = x->parent;
		y = y->parent;
	}
	return y;
}

template <typename K, typename V>
void MyMap<K, V>::clear()
{
	if (root_ == &NIL)
		return;
	TreeDelete(root_);
	root_ = &NIL;
	size_ = 0;
}

template <typename K, typename V>
typename MyMap<K, V>::Iterator MyMap<K, V>::begin()
{
	return Iterator(this, TreeMinimum(root_));
}

template <typename K, typename V>
typename MyMap<K, V>::Iterator MyMap<K, V>::end()
{
	return Iterator(this, &NIL);
}

template <typename K, typename V>
void MyMap<K, V>::TreeDelete(Node *x)
{
	if (x->left != &NIL) {
		TreeDelete(x->left);
	}
	if (x->right != &NIL) {
		TreeDelete(x->right);
	}
	delete x;
}

template <typename K, typename V>
void MyMap<K, V>::dump()
{
	for (MyMap<K, V>::Iterator it = (*this).begin(); it != (*this).end(); ++it){
		cout << it->key << " -- " << it->value << endl;
	}
}