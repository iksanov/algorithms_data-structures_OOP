// 2. ����������� merge sort ��� ���������� ������������ ������.
//��� ��������� ������������ ���������� ������������� ������� ���������.

using namespace std;
#include <algorithm>
typedef int myType;
bool comparator(void* x, void* y) //������� ��������� (����������). ���� ����� �������� ������ ������� - ���������� true, ����� false
{
	myType *x_ = (myType *)x;
	myType *y_ = (myType *)y;
	return (*x_ < *y_);
}
//������� ��� �������� ������� ���� (pElement + (size * x)) (���������� ��������� �� ����������� ��� ������ ������)
void* count(void* pElement, int x, size_t size)
{
	return (void*)((char*)pElement + x*size);
}
void mergeABtoC(void* pElement, int aLength, void* tmp, int bLength, void* c, size_t size, bool(*comparator)(void*, void*)) //������� ��� ������� � ����
{
	for (int i = 0, j = 0, k = 0; k < aLength + bLength; k++) {
		if (i == aLength) { //��������� ��� ����, ��� ������ � ����� ���� ��� ��������� ������������� � �����
			memcpy(count(c, k, size), count(tmp, (j++), size), size);
		}
		else{
			if (j == bLength) { // ��������� ��� ����, ��� ������ � ����� ���� ��� ��������� ������������� � �����
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
//���������� ��������� ������ ������� � ������� � ����
//�� ����: ������ ������ � ��� �����, ������ ������ � ��� �����, 
void mergeSort_(void* pElement, void* tmp, int l, int r, size_t size, bool(*comparator)(void*, void*))
{

	if (r - l < 1) return; //���������: ���� ����� ������� ����� 1, �� �� ��� ������������

	int m = (l + r) / 2; //������� ��������

	mergeSort_(tmp, pElement, l, m, size, comparator); //�������� � ����� ���������
	mergeSort_(tmp, pElement, m + 1, r, size, comparator); //�������� � ������ ���������
	mergeABtoC(count(tmp, l, size), m - l + 1, count(tmp, (m + 1), size), r - m, count(pElement, l, size), size, comparator); //������� � ����
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
	myType* tmp = new myType[length]; // ��������������� ������, ����������� ���� ������� � ������� ��������� �������(� ��� ����� ����������� ������, � ����� ������ ��� � �������� ������ � ������)
	mergeSort(pElement, tmp, length, sizeof(myType));
	return 0;
}