// 7. На основе задачи "Binary Heap" реализовать пирамидальную сортировку.
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
void build_heap(int* a, int heap_size){ //функция строит кучу с максимизирующем свойством
	for (int i = ((heap_size / 2) - 1); i >= 0; i--){ //работаем только с теми элементами, у которых есть потомки
		heapify(a, heap_size, i);
	}
}
void heapSort(int* a, int heap_size) //главная функция сортировки
{
	build_heap(a, heap_size); //строим кучу
	for (int i = heap_size -1; i >= 1; i--){
		swap(a[0], a[i]); //меняем последний элемент с корнем, тем самым удаляем максимальный элемент из дерева, помещая его в нужное место массива
		--heap_size;
		heapify(a, heap_size, 0); //восстанавливаем максимизирующее свойство кучи на 0-ом месте (там теперь стоит последний элемент)
	}
}
int main()
{
	int heap_size = 5;
	int a[] = { 0, 1, 7, 1, 4 };
	heapSort(a, heap_size);
	return 0;
}