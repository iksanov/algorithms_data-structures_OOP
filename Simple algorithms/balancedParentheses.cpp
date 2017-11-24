// 3.8 Напишите программу, которая вычисляет число Cn правильных скобочных структур длины 2n.

#include <new>
#include <iostream>
using namespace std;

void dataInput(int &n) //считываем n
{
	scanf_s("%d", &n);
}
void solution(int* array, int n)
{
	array[0] = 1; //начальное значение рекурентной формулы
	for (int i = 1; i <= n; i++){ // в цикле последовательно считаем числа Каталана
		array[i] = ((4 * i - 2) * array[i - 1]) / (i + 1); 
	}
}
void dataOutput(int res) //выводим результат
{
	printf("%d", res);
}
int main(){
	int n = 0; //количесвто, которое считываем
	dataInput(n);
	int* array = new int[n + 1];
	solution(array, n);
	dataOutput(array[n]);
	return 0;
}