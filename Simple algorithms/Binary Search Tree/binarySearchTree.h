#include <iostream>
#include <iomanip>
template <typename Item >
class BSTree{
	struct Node{
		Item& i;
		Node* p; //родитель
		Node* l; //левый потомок
		Node* r; //правый потомок
		Node(Item&i) :i(i), p(nullptr), l(nullptr), r(nullptr){}
		int key() { return i.key(); }
		bool isLeft() { return p->l == this; }
		bool isRight() { return p->r == this;  }

		void setLeft(Node*l){
			this->l = l;
			if (l != 0)l->p = this;
		}
		void setRight(Node*l){
			this->r = r;
			if (r != 0)r->p = this;
		}
	};
	typedef Node* Link;
	Link root;
	void setRoot(Link x) {
		root = x;
		if (x != 0) x->p = 0;
	}
	void destroy(Link x){
		if (x != 0){
			destroy(x->l);
			destroy(x->r);
			if (x == root) {
				root = 0;
			}
			delete x;
		}
	}
	int count(Link x){
		if (x == 0) return 0;
		return count(x->l) + count(x->r) + 1;
	}
	int height(Link x){
		if (x == 0) return 0;
		int hl = height(x->l) + 1;
		int hr = height(x->r) + 1;
		return hl > hr ? hl : hr;
	}
	Link search(Link x, int key){
		while (x != 0 && x->key() != key)
			if (key < x->key()) x = x->l;
			else x = x->r;
			return x;
	}
	Link min(Link x){
		while (x->l != 0) x = x->l;
		return x;
	}
	Link max(Link x){
		while (x->r != 0) x = x->r;
		return x;
	}
	Link insertionPoint(int key){
		Link x = root;
		Link y = 0;
		while (x != 0){
			y = x;
			if (key < x->key()) x = x->l;
			else x = x->r;
		}
		return y;
	}
	void transplant(Link x, Link y){
		if (x->p == 0) setRoot(y);
		else if (x->isLeft())x->p->setLeft(y);
		else x->p->setRight(y);
	}
	void traverse(Link x, int h, void(*traverseProc)(Item* x, int h)){
		if (x == 0) { traverseProc(0, h); return; }
		traverse(x->r, h + 1, traverseProc);
		traverseProc(&x->i, h);
		traverse(x->l, h + 1, traverseProc);
	}
	
public:
	BSTree() :root(0){}
	~BSTree(){ destroy(root); }
	int count(){ return count(root); }
	int height(){ return height(root); }
	Item* search(int key){
		Link x = search(root, key);
		if (x != 0) return &x->i;
		return 0;
	}
	void insert(Item&i){
		Link p = insertionPoint(i.key());
		Link x = new Node(i);
		if (p == 0) setRoot(x);
		else{
			x->p = p;
			if (i.key() < p->key())p->l = x;
			else p->r = x;
		}
	}
	void insert(Item* Items, int n){
		for (int i = 0; i < n; i++) insert(Items[i]);
	}

	bool remove(int key)
	{
		Link x = search(root, key);
		if (x == 0) return false;
		if (x->l == 0){
			transplant(x, x->r);
		}
		else{
			if (x->r == 0){
				transplant(x, x->l);
			}
			else{
				Link y = min(x->r);
				if (y->p != x){
					transplant(y, y->r);
					y->setRight(x->r);
				}
				transplant(x, y);
				y->setLeft(x->l);
			}
		}
		delete x;
		return true;
	}
	void removeAll() { destroy(root); }
	typedef void(*TraverseProc)(Item* x, int h);
	void traverse(TraverseProc proc){
		traverse(root,0,proc);
	}
	void show(){
		using namespace std;
		cout << endl;
		traverse([](Item*x, int h){
			for (int i = 0; i < h; i++) cout << " ";
			if (x != 0) cout << *x;
			else cout << "*";
			cout << endl;
		});
		cout << endl;
	}
};