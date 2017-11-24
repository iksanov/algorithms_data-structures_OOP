// 6. ����������� ��������� ������ BinaryHeap.
using namespace std;
#include <algorithm>
int left(int i) //������ ������ �������
{
	return 2 * i + 1;
}
int right(int i) //������ ������� �������
{
	return 2 * i + 2;
}
int parent(int i) { //������ ��������
	return (i - 1) / 2;
}
void heapify(int* a, int heap_size, int i) //������� ��������������� ��������������� �������� ���� ��� ��������� ����� i-��� ����
{
	int largest = i;
	if (left(i) <= heap_size - 1 && a[left(i)] > a[largest]){ //��������� ������� ������ ������� � ���������� � ���
		largest = left(i);
	}
	if (right(i) <= heap_size - 1 && a[right(i)] > a[largest]){ //��������� ������� ������� ������� � ���������� � ���
		largest = right(i);
	}
	if (largest != i){
		swap(a[i], a[largest]);
		heapify(a, heap_size, largest); //����������� ����� (���������� "��������" ��� �������)
	}
}
void add(int* a, int &heap_size, int value)//������� ��������� �������� � ���� ���������� ����� (value)
{
	a[heap_size] = value;
	int index = heap_size;
	while ((index > 0) && (a[index] > a[parent(index)])){
		swap(a[index], a[parent(index)]);
		index = parent(index);
	}
	++heap_size;
}
void build_heap(int* a, int heap_size){ //������� ������ ���� � ��������������� ���������
	for (int i = ((heap_size / 2) - 1); i >= 0; i--){ //�������� ������ � ���� ����������, � ������� ���� �������
		heapify(a, heap_size, i);
	}
}
int getMax(int* a, int &heap_size) //������� ���������(����������) ���������, �������������� ����� ����� ��������������� �������� ����
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