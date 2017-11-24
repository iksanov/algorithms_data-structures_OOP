// 2.11 Реализуйте поразрядную сортировку для чисел типа int
#include <new>
//функция возвращает максимум массива array длины length
int get_max(int* array, int length)
{
	int max = array[0]; //максимум
	for (int i = 1; i < length; i++){
		if (array[i] > max){
			max = array[i];
		}
	}
	return max;
}
//сортировка подсчётом
//на вход - массив, длина массива, порядок числа
int digit(int element, int exp){ //функция считает выражение: (array[i] / exp) % 10 (на вход: element = array[i] и exp)
	return (element / exp) % 10;
}
void count_sort(int* array, int length, int exp)
{
	int* tmp = new int[length]; //создаем временный массив tmp
	int count[10] = { 0 }; //создаем массив count
	for (int i = 0; i < length; i++){ //считает, сколько чисел в конкретном разряде имеют определенную цифру и заносит это в массив count
		count[digit(array[i], exp)]++;
	}
	for (int i = 1; i < 10; i++){ //счиатем в массиве частичные суммы
		count[i] += count[i - 1];
	}
	for (int i = length - 1; i >= 0; i--){ //заполняем массив tmp
		tmp[count[digit(array[i], exp)] - 1] = array[i];
		count[digit(array[i], exp)]--;
	}
	for (int i = 0; i < length; i++){ //переносим данные из вспомогательного массива tmp в основной массив array
		array[i] = tmp[i];
	}
	delete[] tmp;
}
//поразрядная сортировка
//на вход - массив и его длина
void radix_sort(int* array, int length)
{
	int max = get_max(array, length); //находим максимальное число массива (число с наибольшим количеством разрядов)
	for (int exp = 1; (max / exp) > 0; exp *= 10){ //цикл проходит по разрядам чисел
		count_sort(array, length, exp); //для каждого разряда вызываем сортировку посчётом
	}
}

int main()
{
	int length = 7;
	int array[] = { 39, 15, 8, 10, 13, 271, 5 };
	radix_sort(array, length);
	return 0;
}