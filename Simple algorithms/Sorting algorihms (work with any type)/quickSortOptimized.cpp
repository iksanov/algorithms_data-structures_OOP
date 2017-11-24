// 10. Реализовать быструю сортировку, сортирующую произвольные данные, в виде отдельной функции.
//В качестве функции сравнения использовать переданную пользователем функцию обратного вызова.
//Реализуйте известные вам методы избежать деградации.
//using namespace std;
#include <algorithm>
#include "generateRandomArray.h"
#include <string.h>
typedef int myType;
void swap(void *a, void *b, size_t size) { //функция меняет между собой содержимое ячеек (принимает два указателя на ячейки и размер типа данных)
	char* tmp = new char[size];
	memcpy(tmp, b, size);
	memcpy(b, a, size);
	memcpy(a, tmp, size);
	delete[] tmp;
}
bool comparator(void* x, void* y) //функция сравнения (компаратор). Если левый аргумент меньше правого - возвращает true, иначе false
{
	myType *x_ = (myType *)x;
	myType *y_ = (myType *)y;
	return (*x_ < *y_);
}
void* count(void* pElement, int x, size_t size)
{
	return (void*)((char*)pElement + x*size);
}
void insertionSort(void* pElement, int length, size_t size, bool(*comparator)(void*, void*)) //сортировка вставками
{

	for (int i = 1; i < length; i++){
		int j = i - 1;
		while (j >= 0 && comparator(count(pElement, j, size), count(pElement, i, size))){
			memcpy(count(pElement, j + 1, size), count(pElement, j, size), size);
			--j;
		}
		memcpy(count(pElement, j + 1, size), count(pElement, i, size), size);
	}
}
//функция для подсчета формулы вида (pElement + (size * x)) (возвращает указатель на необходимую нам ячейку памяти)
//разбиение массива (слева от опорного будут меньшие либо равные ему элементы, а справа - сторого большие)
//возвращаем положение (индекс) опорного элемента при данных условиях
int partition(void* pElement, int l, int r, size_t size, bool(*comparator)(void*, void*))
{
	int randomIndex = random(l, r);
	swap(count(pElement, randomIndex, size), count(pElement, r, size), size); //pivot(опорный элемент) выбираем рандомно
	for (int i = l; i < r; i++){
		if (comparator(count(pElement, i, size), count(pElement, r, size)) || (!(comparator(count(pElement, i, size), count(pElement, r, size))) && !(comparator(count(pElement, r, size), count(pElement, i, size))))){ //pElement + size * i <= pivot, где pivot = pElement + size * r (крайне правый элемент)
			swap(count(pElement, i, size), count(pElement, l, size), size);
			++l;
		}
	}
	swap(count(pElement, r, size), count(pElement, l, size), size);
	return l;
}
void quickSort_(void* pElement, int l, int r, size_t size, bool(*comparator)(void*, void*)){
	if ((r - l) < 10){ //для сортировки малых подмассивов используем более простую сортировку (например, сортировку вставками)
		insertionSort(count(pElement, l, size), r - l + 1, size, comparator);
		return;
	}
	int broad = partition(pElement, l, r, size, comparator); //board - граничный элемент
	quickSort_(pElement, l, broad - 1, size, comparator); //рекурсивно вызываем для левой части
	quickSort_(pElement, broad + 1, r, size, comparator); //рекурсивно вызываем для правой части
}
void quickSort(void* pElement, int length, size_t size)
{
	quickSort_(pElement, 0, length - 1, size, comparator);
}
int main()
{
	int length = 6;
	myType pElement[] = { 5, 1, 4, 3, 10, 3 };
	quickSort(pElement, length, sizeof(myType));
	return 0;
}