#include"binarySearchTree.h"
using namespace std;
struct charItem{
	char c;
	int key() { return c; }
};

ostream& operator << (ostream& os, const charItem& i)
{
	os << i.c;
	return os;
}
void testBST()
{
	charItem C[] { {'E'}, { 'D' }, { 'H' }, { 'B' }, { 'F' }, { 'A' }, { 'C' }, { 'G' }};
	BSTree<charItem>tree;
	tree.insert(C, sizeof(C) / sizeof(*C));
	tree.show();
}

void main()
{
	testBST();
}