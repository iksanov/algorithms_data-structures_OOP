#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//убрать совсем деструктор и принт из дочерних классов, там где он ничего не делает. И сделать абсолютно виртуальную функцию просто виртуальной. И убрать слова виртуал из дочерних классов.

#include "map_editor.h"
#include <iostream>
#include <sstream>
#include <string>
using std::istringstream;
using std::cin;
using std::cout;
using std::endl;
using std::getline;

class AutoLeakChecker
{
public:
	~AutoLeakChecker()
	{
		_CrtDumpMemoryLeaks();
	}
} global_leak_checker;

int main()
{
	string cmd;
	string str;
	int w = 0;
	int h = 0;
	World* my_world = NULL;
	while (my_world == NULL){ //певрое считывание: можно создать карту, вывести справку или выйти, иначе - ошибка
		cout << "> ";
		//cin >> cmd;
		string cmd;
		string str;
		getline(cin, str);
		istringstream in(str);

		in >> cmd;
		if (cmd == "map"){
			w = 0;
			h = 0;
			in >> w >> h;
			if (w <= 0 || h <= 0) {
				cout << "Incorrect map size" << endl;
				continue;
			}
			my_world = new World(w, h);
			break;
		}
		else{
			if (cmd == "help"){
				print_help();
			}
			else{
				if (cmd == "quit"){
					cout << "Bye!" << endl;
					return 0;
				}
				else{
					cout << "Firstly, you should create a map" << endl;
				}
			}
		}
	}

	while (1){
		cout << "> ";

		string cmd;
		string str;
		getline(cin, str);
		istringstream in(str);

		in >> cmd;
		if (cmd == "show"){
			my_world->show();
		}
		else{
			if (cmd == "dump"){
				my_world->dump();
			}
			else{
				if (cmd == "help"){
					print_help();
				}
				else{
					if (cmd == "create"){
						string smth = "";
						string text = "";
						int depth = 0;
						int height = 0;
						string name = "";
						int x = 0;
						int y = 0;
						int size = 0;
						int hp = 0;
						in >> smth;
						if (smth == "lake"){
							in >> text >> depth >> text >> x >> y >> text >> size;
							if (depth <= 0 || x <= 0 || y <= 0 || size <= 0 || x + size > w || y + size > h ) {
								cout << "Wrong input" << endl;
								continue;
							}
							my_world->add_object(new Lake(x, y, size, depth));
						}
						else
						{
							if (smth == "mountain") {
								int height = 0, x = 0, y = 0, size = 0;
								in >> text >> height >> text >> x >> y >> text >> size;
								if (height <= 0 || x <= 0 || y <= 0 || size <= 0 || x + size > w || y + size > h) {
									cout << "Wrong input" << endl;
									continue;
								}
								my_world->add_object(new Mountain(x, y, size, height));
							}
							else
							{
								if (smth == "forest"){
									in >> text >> x >> y >> text >> size;
									if (x <= 0 || y <= 0 || size <= 0 || x + size > w || y + size > h) {
										cout << "Wrong input" << endl;
										continue;
									}
									my_world->add_object(new Forest(x, y, size));
								}
								else
								{
									if (smth == "hero") {
										in >> name >> text >> x >> y >> text >> hp;
										if (name == "" || x <= 0 || y <= 0 || hp <= 0 || x + 1 > w || y + 1 > h) {
											cout << "Wrong input" << endl;
											continue;
										}
										my_world->add_object(new Hero(x, y, hp, name));
									}
									else
									{
										if (smth == "monster") {
											int x = 0, y = 0, hp = 0;
											in >> text >> x >> y >> text >> hp;
											if (x <= 0 || y <= 0 || hp <= 0 || x + 1 > w || y + 1 > h) {
												cout << "Wrong input" << endl;
												continue;
											}
											my_world->add_object(new Monster(x, y, hp));
										}
										else
										{
											cout << "incorrect type of object." << endl;
											continue;
										}
									}
								}
							}
						}
					}
					else
					{
						if (cmd == "move"){
							move(my_world);
						}
						else
						{
							if (cmd != "quit"){
								cout << "Incorrect command. Try again." << endl;
							}
							else
								break;
						}
					}
				}
			}
		}
	}
	cout << "Bye!" << endl;
	delete my_world;
	return 0;
}