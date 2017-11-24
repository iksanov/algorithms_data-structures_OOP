// 6. Реализовать структуру данных BinaryHeap.
using namespace std;
#include <algorithm>
int left(int i) //индекс левого потомка
{
	return 2 * i + 1;
}
int right(int i) //индекс правого потомка
{
	return 2 * i + 2;
}
int parent(int i) { //индекс родителя
	return (i - 1) / 2;
}
void heapify(int* a, int heap_size, int i) //функция восстанавливает максимизирующее свойство кучи при изменении ключа i-ого узла
{
	int largest = i;
	if (left(i) <= heap_size - 1 && a[left(i)] > a[largest]){ //проверяет наличие левого потомка и сравнивает с ним
		largest = left(i);
	}
	if (right(i) <= heap_size - 1 && a[right(i)] > a[largest]){ //проверяет наличие правого потомка и сравнивает с ним
		largest = right(i);
	}
	if (largest != i){
		swap(a[i], a[largest]);
		heapify(a, heap_size, largest); //рекурсивный вызов (продолжаем "утоплять" наш элемент)
	}
}
void add(int* a, int &heap_size, int value)//функция позволяет добавить в кучу конкретное чилсо (value)
{
	a[heap_size] = value;
	int index = heap_size;
	while ((index > 0) && (a[index] > a[parent(index)])){
		swap(a[index], a[parent(index)]);
		index = parent(index);
	}
	++heap_size;
}
void build_heap(int* a, int heap_size){ //функция строит кучу с максимизирующем свойством
	for (int i = ((heap_size / 2) - 1); i >= 0; i--){ //работаем только с теми элементами, у которых есть потомки
		heapify(a, heap_size, i);
	}
}
int getMax(int* a, int &heap_size) //функция извлекает(возвращает) макисимум, восстанавливая после этого максимизирующее свойство кучи
{
	int res = a[0];
	a[0] = a[heap_size - 1];
	a[heap_size - 1] = 0;
	heap_size = heap_size - 1;
	heapify(a, heap_size, 0);
	return res;
}
int main()
{
	const int maxN = 300;
	int a[maxN] = {0};
	int heap_size = 6;
	a[0] = 8;
	a[1] = 5;
	a[2] = 7;
	a[3] = 1;
	a[4] = 4;
	a[5] = 9;
	build_heap(a, heap_size);
	int max = getMax(a, heap_size);
	//int max1 = getMax(a, heap_size);
	//add(a, heap_size, max1);
	//add(a, heap_size, max);
	return 0;
}