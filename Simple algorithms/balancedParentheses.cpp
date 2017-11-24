// 3.8 �������� ���������, ������� ��������� ����� Cn ���������� ��������� �������� ����� 2n.

#include <new>
#include <iostream>
using namespace std;

void dataInput(int &n) //��������� n
{
	scanf_s("%d", &n);
}
void solution(int* array, int n)
{
	array[0] = 1; //��������� �������� ����������� �������
	for (int i = 1; i <= n; i++){ // � ����� ��������������� ������� ����� ��������
		array[i] = ((4 * i - 2) * array[i - 1]) / (i + 1); 
	}
}
void dataOutput(int res) //������� ���������
{
	printf("%d", res);
}
int main(){
	int n = 0; //����������, ������� ���������
	dataInput(n);
	int* array = new int[n + 1];
	solution(array, n);
	dataOutput(array[n]);
	return 0;
}