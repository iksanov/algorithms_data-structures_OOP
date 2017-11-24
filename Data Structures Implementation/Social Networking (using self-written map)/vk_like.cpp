#include "red_black_tree.h"
//#include <map>
#include <string>
#include <iostream>
using std::string;
//using std::map;
using std::cin;
using std::cout;
using std::endl;
typedef MyMap <string, int> LikeMap;

void add(string name, LikeMap& vk)
{
    if (vk.exist(name) == 1){
        cout << "Already excists" << endl;
        return;
    }
    vk[name] = 0;
}

void erase(string name, LikeMap& vk)
{
    if (vk.exist(name) == false){
        cout << "Doesn't excist" << endl;
        return;
    }
    vk.erase(name);
}

void like(string name, LikeMap& vk)
{
    if (vk.exist(name) == false){
        cout << "Doesn't excist" << endl;
        return;
    }
    ++vk[name];
}

void dislike(string name, LikeMap& vk)
{
    if (vk.exist(name) == false){
        cout << "Doesn't excist" << endl;
        return;
    }
    --vk[name];
}

void show(string name, LikeMap& vk)
{
    if (vk.exist(name) == false){
        cout << "Doesn't excist" << endl;
        return;
    }
    cout << vk[name] << endl;
}

void ddump(LikeMap& vk)
{
    for (LikeMap::Iterator it = vk.begin(); it != vk.end(); ++it)
        cout << it->key << " -- " << it->value << endl;
}

int main()
{
	LikeMap vk;

	string cmd = "";
	string name = "";
	while (cmd != "exit"){
		cin >> cmd;
		if (cmd == "dump"){
			if (vk.empty())
				cout << "Dump is empty." << endl;
			else
				vk.dump();
		}
		if (cmd == "add"){
			cin >> name;
			if (vk.exist(name) == true)
				cout << "Already excists" << endl;
			else
				vk.Insert(name);
		}
		if (cmd == "delete"){
			cin >> name;
			if (vk.exist(name) == false)
				cout << "Doesn't excist" << endl;
			else
				vk.erase(name);
		}
		if (cmd == "like"){
			cin >> name;
			if (vk.exist(name) == false)
				cout << "Doesn't excist" << endl;
			else
				++vk[name];
		}
		if (cmd == "dislike"){
			cin >> name;
			if (vk.exist(name) == false)
				cout << "Doesn't excist" << endl;
			else
				--vk[name];
		}
		if (cmd == "show"){
			cin >> name;
			if (vk.exist(name) == false)
				cout << "Doesn't excist" << endl;
			else
				cout << vk[name];
		}
	}

	cout << "Bye, bye" << endl;
	return 0;
}
