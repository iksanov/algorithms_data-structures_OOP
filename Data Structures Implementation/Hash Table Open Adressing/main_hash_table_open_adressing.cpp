#include "hash_table.h"
#include <string>
using std::string;

int main()
{
	Hashing <int, string> tab;
	tab.insert(1, "01");
	tab.insert(2, "02");
	tab.insert(3, "01");
	Hashing<int, string> new_tab = tab;
	string res = tab.search(2);
	tab.erase(2);
	return 0;
}