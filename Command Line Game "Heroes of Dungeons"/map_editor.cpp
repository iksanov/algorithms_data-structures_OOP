#include "map_editor.h"
#include <string>
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

GameObject::GameObject(int x_, int y_, int size_)
{
	x = x_;
	y = y_;
	size = size_;
}

int GameObject::get_x() const
{
	return x;
}

int GameObject::get_y() const
{
	return y;
}

int GameObject::get_size() const
{
	return size;
}

char GameObject::symbol() const
{
	return '?';
}

void GameObject::move(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
}

Creature::Creature(int x_, int y_, int hp_) :GameObject(x_, y_, 1)
{
	hp = hp_;
}

int Creature::get_hp() const
{
	return hp;
}

char Creature::symbol() const
{
	return '?';
}

Hero::Hero(int x_, int y_, int hp_, string name_) :Creature(x_, y_, hp_)
{
	name = name_;
}

void Hero::print() const
{
	cout << "Great hero " << name << " with hp " << get_hp() << " at " << "(" << get_x() << "," << get_y() << ")" << endl;
}

char Hero::symbol() const
{
	return name[0];
}

Monster::Monster(int x_, int y_, int hp_) :Creature(x_, y_, hp_)
{

}

void Monster::print() const
{
	cout << "Some monster with hp " << get_hp() << " at " << "(" << get_x() << "," << get_y() << ")" << endl;
}

char Monster::symbol() const
{
	return 'm';
}

Terrain::Terrain(int x_, int y_, int size_) :GameObject(x_, y_, size_)
{

}

char Terrain::symbol() const
{
	return '?';
}

Lake::Lake(int x_, int y_, int size_, int depth_) :Terrain(x_, y_, size_)
{
	depth = depth_;
}

void Lake::print() const
{
	cout << "Clean lake of depth " << depth << " at " << "(" << get_x() << "," << get_y() << ") size " << get_size() << endl;
}

char Lake::symbol() const
{
	return '~';
}

Mountain::Mountain(int x_, int y_, int size_, int height_) :Terrain(x_, y_, size_)
{
	height = height_;
}

void Mountain::print() const
{
	cout << "Big mountain " << height << " feet height at (" << get_x() << "," << get_y() << ") size = " << get_size() << endl;
}

char Mountain::symbol() const
{
	return '^';
}
Forest::Forest(int x_, int y_, int size_) :Terrain(x_, y_, size_)
{
	
}

void Forest::print() const
{
	cout << "Forest at (" << get_x() << "," << get_y() << ") size = " << get_size() << endl;
}

char Forest::symbol() const
{
	return 'F';
}

World::World(int width_, int height_)
{
	height = height_;
	width = width_;
	map = new char[height*(width * 2 + 1) + 1];
	render();
}

World::~World()
{
	delete[] map;
	for (int i = 0; i < objects.size(); ++i)
		delete[] objects[i];
}

void World::render()
{
	int xWid = width * 2 + 1; // абсолютная ширина поля
	map[height*xWid] = '\0';
	for (int i = xWid - 1; i < height*xWid; i += xWid)
		map[i] = '\n';
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < xWid - 1; j += 2){
			map[(width * 2 + 1) * i + j] = '.';
			map[(width * 2 + 1) * i + j + 1] = ' ';
		}
	int x0, y0, size;
	char symb;
	for (int i = 0; i < objects.size(); ++i){ //проходимся по массиву с объектами
		x0 = objects[i]->get_x() - 1;
		y0 = objects[i]->get_y() - 1;
		size = objects[i]->get_size();
		symb = objects[i]->symbol();
		for (int x = 0; x < size; ++x) //заполянем карту символами объекта
			for (int y = 0; y < size; ++y){
				map[2*(x0 + x) + (y0 + y)*xWid] = symb;
			}
	}
}

void World::show() const
{
	cout << map;
}

void World::dump() const
{
	if (objects.size() == 0)
		cout << "Dump is empty" << endl;
	for (int i = 0; i < objects.size(); ++i) {
		std::cout << i + 1 << ". ";
		objects[i]->print();
	}
}

void World::add_object(GameObject *new_object)
{
	objects.push_back(new_object);
	render();
}

GameObject* World::get_object(int index) const
{
	return objects[index];
}

void World::move_object(int index, int x, int y)
{
	get_object(index)->move(x, y);
	render();
}

void move(World* my_world)
{
	int new_x = 0;
	int new_y = 0;
	int index = 0;
	cin >> index >> new_x >> new_y;
	my_world->move_object(index-1, new_x, new_y);
}

void print_help()
{
	cout <<
		"1. map (width) (height) - create a new map" << endl <<
		"2. show - print current map" << endl <<
		"3. create lake depth (depth) at (x) (y) size (size)" << endl <<
		"4. create mountain height (height) at (x) (y) size (size)" << endl <<
		"5. create forest at (x) (y) size (size)" << endl <<
		"6. create hero <name> at (x) (y) hp (hp)" << endl <<
		"7. create monster at (x) (y) hp (hp)" << endl <<
		"8. dump - show descriptions of all objects that are on the current map" << endl <<
		"9. help - show instructions" << endl <<
		"10. quit - exit the editor" << endl;
}

//void create_smth(World* my_world)
//{
//	string smth;
//	string text;
//	int depth = 0;
//	int height = 0;
//	string name;
//	int x = 0;
//	int y = 0;
//	int size = 0;
//	int hp = 0;
//	cin >> smth;
//	if (smth == "lake"){
//		cin >> text >> depth >> text >> x >> y >> text >> size;
//		my_world->add_object(new Lake(x, y, size, depth));
//	}
//	else
//	{
//		if (smth == "mountain") {
//			int height = 0, x = 0, y = 0, size = 0;
//			cin >> text >> height >> text >> x >> y >> text >> size;
//			my_world->add_object(new Mountain(x, y, size, height));
//		}
//		else
//		{
//			if (smth == "forest"){
//				cin >> text >> x >> y >> text >> size;
//				my_world->add_object(new Forest(x, y, size));
//			}
//			else
//			{
//				if (smth == "hero") {
//					cin >> name >> text >> x >> y >> text >> hp;
//					my_world->add_object(new Hero(x, y, hp, name));
//				}
//				else
//				{
//					if (smth == "monster") {
//						int x = 0, y = 0, hp = 0;
//						cin >> text >> x >> y >> text >> hp;
//						my_world->add_object(new Monster(x, y, hp));
//					}
//					else
//					{
//						cout << "incorrect type of object." << endl;
//					}
//				}
//			}
//		}
//	}
//}