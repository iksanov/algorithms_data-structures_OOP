// 2.11 ���������� ����������� ���������� ��� ����� ���� int
#include <new>
//������� ���������� �������� ������� array ����� length
int get_max(int* array, int length)
{
	int max = array[0]; //��������
	for (int i = 1; i < length; i++){
		if (array[i] > max){
			max = array[i];
		}
	}
	return max;
}
//���������� ���������
//�� ���� - ������, ����� �������, ������� �����
int digit(int element, int exp){ //������� ������� ���������: (array[i] / exp) % 10 (�� ����: element = array[i] � exp)
	return (element / exp) % 10;
}
void count_sort(int* array, int length, int exp)
{
	int* tmp = new int[length]; //������� ��������� ������ tmp
	int count[10] = { 0 }; //������� ������ count
	for (int i = 0; i < length; i++){ //�������, ������� ����� � ���������� ������� ����� ������������ ����� � ������� ��� � ������ count
		count[digit(array[i], exp)]++;
	}
	for (int i = 1; i < 10; i++){ //������� � ������� ��������� �����
		count[i] += count[i - 1];
	}
	for (int i = length - 1; i >= 0; i--){ //��������� ������ tmp
		tmp[count[digit(array[i], exp)] - 1] = array[i];
		count[digit(array[i], exp)]--;
	}
	for (int i = 0; i < length; i++){ //��������� ������ �� ���������������� ������� tmp � �������� ������ array
		array[i] = tmp[i];
	}
	delete[] tmp;
}
//����������� ����������
//�� ���� - ������ � ��� �����
void radix_sort(int* array, int length)
{
	int max = get_max(array, length); //������� ������������ ����� ������� (����� � ���������� ����������� ��������)
	for (int exp = 1; (max / exp) > 0; exp *= 10){ //���� �������� �� �������� �����
		count_sort(array, length, exp); //��� ������� ������� �������� ���������� ��������
	}
}

int main()
{
	int length = 7;
	int array[] = { 39, 15, 8, 10, 13, 271, 5 };
	radix_sort(array, length);
	return 0;
}