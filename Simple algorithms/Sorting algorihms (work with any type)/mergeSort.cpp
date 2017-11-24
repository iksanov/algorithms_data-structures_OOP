// 2. Реализовать merge sort для сортировки произвольных данных.
//Для сравнения использовать переданную пользователем функцию сравнения.

using namespace std;
#include <algorithm>
typedef int myType;
bool comparator(void* x, void* y) //функция сравнения (компаратор). Если левый аргумент меньше правого - возвращает true, иначе false
{
	myType *x_ = (myType *)x;
	myType *y_ = (myType *)y;
	return (*x_ < *y_);
}
//функция для подсчета формулы вида (pElement + (size * x)) (возвращает указатель на необходимую нам ячейку памяти)
void* count(void* pElement, int x, size_t size)
{
	return (void*)((char*)pElement + x*size);
}
void mergeABtoC(void* pElement, int aLength, void* tmp, int bLength, void* c, size_t size, bool(*comparator)(void*, void*)) //сливаем два массива в один
{
	for (int i = 0, j = 0, k = 0; k < aLength + bLength; k++) {
		if (i == aLength) { //проверяем тот факт, что массив а может быть уже полностью перекопирован в новый
			memcpy(count(c, k, size), count(tmp, (j++), size), size);
		}
		else{
			if (j == bLength) { // проверяем тот факт, что массив а может быть уже полностью перекопирован в новый
				memcpy(count(c, k, size), count(pElement, (i++), size), size);
			}
			else{
				if (comparator(count(pElement, i, size), count(tmp, j, size))){
					memcpy(count(c, k, size), count(pElement, (i++), size), size);
				}
				else{
					memcpy(count(c, k, size), count(tmp, (j++), size), size);
				}
			}
		}
	}
}
//рекурсивно разделяем массив пополам и сливаем в один
//на вход: первый массив и его длина, второй массив и его длина, 
void mergeSort_(void* pElement, void* tmp, int l, int r, size_t size, bool(*comparator)(void*, void*))
{

	if (r - l < 1) return; //проверяем: если длина массива равна 1, то он уже отсортирован

	int m = (l + r) / 2; //находим середину

	mergeSort_(tmp, pElement, l, m, size, comparator); //работаем с левой половиной
	mergeSort_(tmp, pElement, m + 1, r, size, comparator); //работаем с правой половиной
	mergeABtoC(count(tmp, l, size), m - l + 1, count(tmp, (m + 1), size), r - m, count(pElement, l, size), size, comparator); //сливаем в один
}
void mergeSort(void* pElement, void* tmp, int length, size_t size)
{
	for (int i = 0; i < length; i++) {
		memcpy(count(tmp, i, size), count(pElement, i, size), size);
	}
	mergeSort_(pElement, tmp, 0, length - 1, size, comparator);
	delete[] tmp;
}
int main()
{
	myType pElement[] = { 5, 1, 4, 3, 10, 0 };
	int length = 6;
	myType* tmp = new myType[length]; // вспомогательный массив, выполняющий роль гланого в течение некотрого времени(в нем будет происходить работа, п потом сольем его в основной старый и удалим)
	mergeSort(pElement, tmp, length, sizeof(myType));
	return 0;
}