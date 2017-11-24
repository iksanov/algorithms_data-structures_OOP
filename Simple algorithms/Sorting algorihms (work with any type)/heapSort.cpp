// 7. �� ������ ������ "Binary Heap" ����������� ������������� ����������.
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
void build_heap(int* a, int heap_size){ //������� ������ ���� � ��������������� ���������
	for (int i = ((heap_size / 2) - 1); i >= 0; i--){ //�������� ������ � ���� ����������, � ������� ���� �������
		heapify(a, heap_size, i);
	}
}
void heapSort(int* a, int heap_size) //������� ������� ����������
{
	build_heap(a, heap_size); //������ ����
	for (int i = heap_size -1; i >= 1; i--){
		swap(a[0], a[i]); //������ ��������� ������� � ������, ��� ����� ������� ������������ ������� �� ������, ������� ��� � ������ ����� �������
		--heap_size;
		heapify(a, heap_size, 0); //��������������� ��������������� �������� ���� �� 0-�� ����� (��� ������ ����� ��������� �������)
	}
}
int main()
{
	int heap_size = 5;
	int a[] = { 0, 1, 7, 1, 4 };
	heapSort(a, heap_size);
	return 0;
}