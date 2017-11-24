// 10. ����������� ������� ����������, ����������� ������������ ������, � ���� ��������� �������.
//� �������� ������� ��������� ������������ ���������� ������������� ������� ��������� ������.
//���������� ��������� ��� ������ �������� ����������.
//using namespace std;
#include <algorithm>
#include "generateRandomArray.h"
#include <string.h>
typedef int myType;
void swap(void *a, void *b, size_t size) { //������� ������ ����� ����� ���������� ����� (��������� ��� ��������� �� ������ � ������ ���� ������)
	char* tmp = new char[size];
	memcpy(tmp, b, size);
	memcpy(b, a, size);
	memcpy(a, tmp, size);
	delete[] tmp;
}
bool comparator(void* x, void* y) //������� ��������� (����������). ���� ����� �������� ������ ������� - ���������� true, ����� false
{
	myType *x_ = (myType *)x;
	myType *y_ = (myType *)y;
	return (*x_ < *y_);
}
void* count(void* pElement, int x, size_t size)
{
	return (void*)((char*)pElement + x*size);
}
void insertionSort(void* pElement, int length, size_t size, bool(*comparator)(void*, void*)) //���������� ���������
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
//������� ��� �������� ������� ���� (pElement + (size * x)) (���������� ��������� �� ����������� ��� ������ ������)
//��������� ������� (����� �� �������� ����� ������� ���� ������ ��� ��������, � ������ - ������� �������)
//���������� ��������� (������) �������� �������� ��� ������ ��������
int partition(void* pElement, int l, int r, size_t size, bool(*comparator)(void*, void*))
{
	int randomIndex = random(l, r);
	swap(count(pElement, randomIndex, size), count(pElement, r, size), size); //pivot(������� �������) �������� ��������
	for (int i = l; i < r; i++){
		if (comparator(count(pElement, i, size), count(pElement, r, size)) || (!(comparator(count(pElement, i, size), count(pElement, r, size))) && !(comparator(count(pElement, r, size), count(pElement, i, size))))){ //pElement + size * i <= pivot, ��� pivot = pElement + size * r (������ ������ �������)
			swap(count(pElement, i, size), count(pElement, l, size), size);
			++l;
		}
	}
	swap(count(pElement, r, size), count(pElement, l, size), size);
	return l;
}
void quickSort_(void* pElement, int l, int r, size_t size, bool(*comparator)(void*, void*)){
	if ((r - l) < 10){ //��� ���������� ����� ����������� ���������� ����� ������� ���������� (��������, ���������� ���������)
		insertionSort(count(pElement, l, size), r - l + 1, size, comparator);
		return;
	}
	int broad = partition(pElement, l, r, size, comparator); //board - ��������� �������
	quickSort_(pElement, l, broad - 1, size, comparator); //���������� �������� ��� ����� �����
	quickSort_(pElement, broad + 1, r, size, comparator); //���������� �������� ��� ������ �����
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