#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "red_black_tree.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class AutoLeakChecker{
public:
	~AutoLeakChecker()
	{
		_CrtDumpMemoryLeaks();
	}
} global_leak_checker;

int main()
{
	MyMap <int, double> test;
	test.Insert(2, 2.02);
	test.Insert(2, 2.02);
	test.Insert(2, 2.02);
	test.Insert(2, 2.02);
	test.Insert(2, 2.02);
	test.Insert(3, 2.03);
	test.Insert(4, 2.04);
	test.erase(2);
	test.erase(2);
	test.erase(2);
	double f = test[11];
	test.erase(2);
	MyMap<int, double>::Iterator it = test.end();
	cout << (*it).key << " -- " << (*it).value << endl << endl;

	test.dump();

	int ssize = test.size();

	bool r = test.exist(3);

	test.clear();
	int sssize = test.size();
	if (test.empty())
		cout << "Is really empty" << endl;
	return 0;
}