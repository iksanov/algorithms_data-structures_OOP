#pragma once

template <class TKey, class TValue>
class MyMap
{
private:

	struct Node
	{
		friend class MyMap;
		TKey key;
		TValue value;
		Node(const TKey key_ = TKey(), const TValue value_ = TValue(), char color = 'R'){
			right = &nil;
			left = &nil;
			parent = &nil;
			key = key_;
			value = value_;
			color = color;
		}

		Node *right;
		Node *left;
		Node *parent;

		char color;
	};

	static Node nil;
	Node *root;
	int size_;

	void LeftRotate(Node *x);
	void RightRotate(Node *y);
	void InsertFixUp(Node* z);
	Node *TreeSearch(const TKey key) const;
	void Transplant(Node *u, Node *v);
	Node *TreeMinimum(Node *x) const;
	void eraseFixup(Node *x);
	Node *TreeSuccessor(Node *x);
	void TreeDelete(Node *x);
public:
	MyMap()
	{
		root = &nil;
		size_ = 0;
	}
	void Insert(const TKey key_, const TValue value_ = TValue());
	TValue &operator[](const TKey key);
	void erase(TKey key);
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
	bool exist(TKey key)
	{
		bool tmp;
		if (TreeSearch(key) == &nil)
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

template <class TKey, class TValue>
typename MyMap<TKey, TValue>::Node MyMap<TKey, TValue>::nil(TKey(), TValue(), 'B');

template <class TKey, class TValue>
void MyMap<TKey, TValue>::LeftRotate(Node *x)
{
	Node *y = new Node;
	y = x->right;
	x->right = y->left;
	if (y->left != &nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == &nil) {
		this->root = y;
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

template <class TKey, class TValue>
void MyMap<TKey, TValue>::RightRotate(Node *y)
{
	Node *x = new Node;
	x = y->left;
	y->left = x->right;
	if (x->right != &nil)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == &nil) {
		root = x;
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

template <class TKey, class TValue>
void MyMap<TKey, TValue>::Insert(const TKey key_, const TValue value_)
{
	Node* z = new Node(key_, value_, 'R');
	Node *y = &nil;
	Node *x = root;
	while (x != &nil) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == &nil) {
		root = z;
	}
	else {
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	}
	InsertFixUp(z);
}

template <class TKey, class TValue>
void MyMap<TKey, TValue>::InsertFixUp(Node* z)
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
	root->color = 'B';
	++size_;
}

template <class TKey, class TValue>
typename MyMap<TKey, TValue>::Node *MyMap<TKey, TValue>::TreeSearch(const TKey key) const
{
	Node *x = root;
	while (x != &nil && key != x->key) {
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template <class TKey, class TValue>
TValue &MyMap<TKey, TValue>::operator[](const TKey key)
{
	Node *x = TreeSearch(key);
	if (x == &nil) {
		Insert(key);
		x = TreeSearch(key);
	}
	return x->value;
}

template <class TKey, class TValue>
void MyMap<TKey, TValue>::Transplant(Node* u, Node* v)
{
	if (u->parent == &nil)
		root = v;
	else
		if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
	v->parent = u->parent;
}

template <class TKey, class TValue>
void MyMap<TKey, TValue>::erase(TKey key)
{
	Node *z = TreeSearch(key);
	Node *y = z;
	char y_original_color = y->color;
	if (z == &nil)
		return;
	Node *x;
	if (z->left == &nil) {
		x = z->right;
		Transplant(z, z->right);
	}
	else{
		if (z->right == &nil) {
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

template <class TKey, class TValue>
typename MyMap<TKey, TValue>::Node *MyMap<TKey, TValue>::TreeMinimum(Node *x) const
{
	while (x->left != &nil)
		x = x->left;
	return x;
}

template <class TKey, class TValue>
void MyMap<TKey, TValue>::eraseFixup(Node *x)
{
	while (x != root && x->color == 'B') {
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
				x = root;
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
				x = root;
			}
			delete w;
		}
	}
	x->color = 'B';
}

template <class TKey, class TValue>
typename MyMap<TKey, TValue>::Node *MyMap<TKey, TValue>::TreeSuccessor(Node *x)
{
	if (x->right != &nil) {
		return TreeMinimum(x->right);
	}
	Node *y = x->parent;
	while (y != &nil && x == y->right) {
		x = x->parent;
		y = y->parent;
	}
	return y;
}

template <class TKey, class TValue>
void MyMap<TKey, TValue>::clear()
{
	if (root == &nil)
		return;
	TreeDelete(root);
	root = &nil;
	size_ = 0;
}

template <class TKey, class TValue>
typename MyMap<TKey, TValue>::Iterator MyMap<TKey, TValue>::begin()
{
	return Iterator(this, TreeMinimum(root));
}

template <class TKey, class TValue>
typename MyMap<TKey, TValue>::Iterator MyMap<TKey, TValue>::end()
{
	return Iterator(this, &nil);
}

template <class TKey, class TValue>
void MyMap<TKey, TValue>::TreeDelete(Node *x)
{
	if (x->left != &nil) {
		TreeDelete(x->left);
	}
	if (x->right != &nil) {
		TreeDelete(x->right);
	}
	delete x;
}

template <class TKey, class TValue>
void MyMap<TKey, TValue>::dump()
{
	for (MyMap<TKey, TValue>::Iterator it = (*this).begin(); it != (*this).end(); ++it){
		cout << it->key << " -- " << it->value << endl;
	}
}