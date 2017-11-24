#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <type_traits>
using std::is_pointer;
using std::string;
using std::hash;
using std::cin;
using std::cout;
using std::endl;

const size_t initial_size = 10;

//#define elem Element<TKey, TValue>;

template <typename TKey, typename TValue>
class Hashing
{
public:
	Hashing()
	{
		capacity = initial_size;
		size = 0;
		table = new Element[capacity];
	}

	~Hashing()
	{
		delete[] table;
	}

	Hashing(const Hashing& ht)
	{
		table = 0; //чтобы далее в операторе присваивания при вызове delete table не было проблем (так как до этого table была еще пустая и не ининциализированная)
		*this = ht;
	}

	Hashing &operator=(const Hashing& ht)
	{
		if (&ht == this) return *this;
		capacity = ht.capacity;
		size = ht.size;
		delete[] table;
		table = new Element[capacity];
		for (size_t i = 0; i < capacity; ++i){
			if (ht.table[i].state != 'F')
				table[i] = ht.table[i];
		}
//будет ли здесь вызываться конструктор копирования? Если да, то нормально ли реализовывать равно через констр., а констр. через равно (как сейчас у меня)?
		return *this;
	}

	void resize_table()
	{
		Hashing tmp;
		tmp.capacity = capacity * 2;
		delete[] tmp.table;
		tmp.table = new Element[tmp.capacity];
		for (size_t i = 0; i < size; ++i){
			tmp.insert(table[i].key, table[i].value);
		}
		*this = tmp;
	}

	void insert(const TKey key, const TValue value = TValue())
	{
		size_t hash_value = hash_function(key);
		for (size_t i = 0; i < capacity; ++i){
			size_t current_hash_value = (hash_value + i) % capacity;
			if (table[current_hash_value].state != 'B'){ //будем бежать по всем ячейкам таблицы, начиная с той, куда хотели положить, пока не найдем свободную
				table[current_hash_value] = Element(key, value);
				++size;
				break;
			}
		}
		if (size == capacity)
			resize_table();
	}

	Element element_search(const TKey key) const{
		size_t hash_value = hash_function(key);
		for (size_t i = 0; i < capacity; ++i){
			size_t current_hash_value = (hash_value + i) % capacity;
			if (table[current_hash_value].state == 'B' && table[current_hash_value].key == key)
					return table[current_hash_value].value;
			else
				if (table[current_hash_value].state == 'F')
					break;
//////////////////////////////// сюда мы прикрутим итераторы			
		}
		cout << "Can't search. No elements with this key." << endl;
		return NULL;
	}

	void erase(const TKey key)
	{
		size_t hash_value = hash_function(key);
		for (size_t i = 0; i < capacity; ++i){
			size_t current_hash_value = (hash_value + i) % capacity;
			if (table[current_hash_value].state == 'B' && table[current_hash_value].key == key){
				table[current_hash_value].state = 'D';
				--size;
				return;
			}
			else
				if (table[current_hash_value].state == 'F')
					break;
		}
		cout << "Can't erase. No elements with this key." << endl;
	}

	TValue &operator[](const TKey key)
	{
		Element x = element_search(key);
		if (x == &NIL) {
			Insert(key);
			x = TreeSearch(key);
		}
		return x->value;
	}

	//class Iterator {
	//private:
	//	friend class Hashing;
	//	Element* elem; //элемент, на который будет указывать итератор
	//	Iterator(Element* elem_) : elem(elem_) {}
	//public:
	//	Iterator(const Iterator& it) : elem(it.elem) {}
	//	Iterator begin();
	//	Iterator end();
	//
	//}

	//template <typename TKey, typename TValue>
	//typename Hashing <TKey, TValue>::Iterator Hashing <TKey, TValue>::begin()
	//{
	//	return Iterator(table[0]);
	//}
	
private:
	struct Element
	{
		Element()
		{
			key = TKey();
			value = TValue();
			state = 'F';
		}
		Element(const TKey key_, const TValue value_) : key(key_), value(value_)++++
		{
			state = 'B';
		}
		TKey key;
		TValue value;
		char state; // F - free, B - busy, D - deleted
	};
	Element *table;
	size_t capacity;
	size_t size; //количество занятых ячеек
	size_t hash_function(TKey key) const{
		hash<TKey> h_function;
		return h_function(key) % capacity;
	}

	friend class Iterator;
};