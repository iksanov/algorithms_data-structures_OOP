#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class GameObject
{
public:
	GameObject(int x, int y, int size);
	virtual ~GameObject(){}
	int get_x() const;
	int get_y() const;
	int get_size() const;
	void move(int new_x, int new_y); // переместить объект в новую позицию
	virtual char symbol() const = 0; // символ, которым отрисовывается объект
	virtual void print() const = 0; // вывести на экран описание
private:
	int x, y;
	int size;
};

class Creature :public GameObject
{
private:
	int hp;
public:
	Creature(int x, int y, int hp);
	virtual ~Creature(){}
	int get_hp() const;
	virtual char symbol() const;
	virtual void print() const{}
};

class Hero :public Creature
{
private:
	string name;
public:
	Hero(int x, int y, int hp, string name);
	virtual ~Hero(){}
	virtual char symbol() const;
	virtual void print() const;
};

class Monster :public Creature
{
public:
	Monster(int x, int y, int hp);
	virtual ~Monster(){}
	virtual char symbol() const;
	virtual void print() const;
};

class Terrain :public GameObject
{
public:
	Terrain(int x, int y, int size);
	virtual ~Terrain(){}
	virtual char symbol() const;
	virtual void print() const{}
};

class Lake :public Terrain
{
private:
	int depth;
public:
	Lake(int x, int y, int size, int depth);
	virtual ~Lake(){}
	virtual char symbol() const;
	virtual void print() const;
};

class Mountain :public Terrain
{
private:
	int height;
public:
	Mountain(int x, int y, int size, int height);
	virtual ~Mountain(){}
	virtual char symbol() const;
	virtual void print() const;
};

class Forest :public Terrain
{
private:
	int depth;
public:
	Forest(int x, int y, int size);
	virtual ~Forest(){}
	virtual char symbol() const;
	virtual void print() const;
};

class World {
public:
	World(int width, int height); // инициализирует все поля, вызывает render() для создания пустой карты
	~World(); // удаляет картину мира и все объекты, т.е. проходится по ``objects`` и для каждого элемента вызывает ``delete``
	void show() const; // выводит на экран текущую картину мира (``std::cout << map;``)
	void dump() const;
	void add_object(GameObject *new_object); // добавляет указатель на вновь созданный объект в массив ``objects`` и вызывает ``render()``
	void move_object(int index, int new_x, int new_y); // переместить объект в новую позицию
private:
	int width, height;
	void render(); // заполняет картину мира (``map``), но не отрисовывает ее. Вызывается каждый раз после ``add_object``
	vector<GameObject *> objects; // массив указателей на объекты. Те, кто умеют обращаться с ``std::vector``, пусть используют его
	char *map; // Cтрока размера ``height*(width * 2 + 1) + 1`` (подумайте, почему именно такого), содержащая в себе полную картину мира (т.е. все переводы строк уже включены)
	GameObject* get_object(int index) const;
	World(const World&) = delete;  // запретить копирование (любители c++11 могут использовать ``=delete``)
	void operator=(const World&); // запретить присваивание (любители c++11 могут использовать ``=delete``)
};

//void create_smth(World*);

void print_help();

void move(World*);