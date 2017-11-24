﻿// 3.3 Будем называть натуральное число трипростым, если в нем любые подряд идущие 3 цифры образуют трехзначное простое число.
//Требуется найти количество N-значных трипростых чисел.
//Входной файл INPUT.TXT содержит натуральное число N (3 ≤ N ≤ 10000).
//Выходной файл OUTPUT.TXT должен содержать количество N-значных трипростых чисел, которое следует вывести по модулю 109+9.

#include <new>
#include <math.h>
#include <fstream>
//проверяет число n на простоту алгоритмом перебора до корня из x (возвращает true, если простое, false, если непростое)
bool isPrimeAlgo(int x)
{
	int count = 0; //количество делителей нашего числа от двойки до корня
	for (int i = 2; i <= sqrt((double)x); i++)
	{
		if (x % i == 0) ++count;
	}
	return (x > 1) && (count == 0);
}
//проверяет число n на простоту через проверку принадлежности к массиву tmp длины length (возвращает true, если простое, false, если непростое)
bool isPrimeCheck(int x, int* tmp, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (x == tmp[i]) return true;
	}
	return false;
}
int findNumbers(int n) //ищем количество трипростых чисел длины n (возсращает количество)
{
	int mod = 1000000009; //модуль, по которому нам нужно вывести ответ
	int** array = new int*[n + 1]; //создаем двумерный массив размера (n+1 x 100)
	for (int i = 0; i <= n; ++i) array[i] = new int[100]; //строки - n (количество трипростых чисел), столбцы - остатки от деления трехзначных чисел на 100 (0..99)
	for (int i = 0; i <= n; ++i) { //зануляем наш массив
		for (int j = 0; j < 100; ++j) {
			array[i][j] = 0;
		}
	}
	int tmp[900] = {0}; //временный массив, в котором будут лежать простые трехзначные числа
	int count = 0; //счетчкик для нашего врменного массива tmp
	for (int i = 100; i < 1000; ++i) { //считаем трипростые числа длины 3 (просто трехзначные простые числа)
		if (isPrimeAlgo(i)) {
			++(array[3][i % 100]); //заносим результат в таблицу (в третью строчку, в ячейку, равную остатку от деления этого числа на 100
			tmp[count++] = i; //добавляем число во временный массив простых трехзначных чисел, увеличиваем счетчик
		}
	}
	for (int i = 4; i <= n; ++i) { //цикл обеспечивает проход от 4-ой строчки таблицы до n-ой
		for (int j = 0; j <= 99; ++j) { //цикл обеспечивает проход по остаткам от деления на 100
			for (int k = 0; k <= 9; ++k) { //цикл обеспечивает проход по последней цифре числа, описанного ниже
				int number = 10 * j + k; //число, сформированное из чисел j и k (здесь будут все числа от 0 до 999)
				if (isPrimeCheck(number,tmp,count)) { //если число - простое
					array[i][number % 100] = (array[i][number % 100] + array[i - 1][j]) % mod;// результат берем по модулю, чтобы не было переполнения
					//в ячейку числа длины n, начинающегося на j, добавляем результат, хранящийся в ячейке числадлины  n-1, заканчивающегося на j
					//(в нашем случае - трехзначное число начинается на j, а случае n-1 трехзначное число заканчивалось на j)
				}
			}
		}
	}
	int res = 0; //итоговый ответ
	for (int j = 0; j <= 99; ++j) { //пробегаем по строке с номером n и суммируем количество трипростых чисел данной длины (n)
		res = (res + array[n][j]) % mod; //результат берем по модулю
	}
	for (int i = 0; i <= n; i++) delete[] array[i];
	delete[] array;
	return res;
}
void dataInput(FILE* input, int &n) //считываем n - длина трипростых чисел (на вход: файл ввода, переменная n)
{
	fscanf_s(input, "%d", &n);
}
void dataOutput(FILE* output, int res) //выводим res - количество трипростых чисел заданной длины n (на вход: файл вывода, переменная res)
{
	fprintf(output, "%d", res);
}
int main()
{
	FILE *input, *output;
	fopen_s(&input, "INPUT.TXT", "r");
	fopen_s(&output, "OUTPUT.TXT", "w");
	int n = 0; //переменная для длины трипростых чисел
	int res = 0; //переменная для результата - количествf трипростых чисел заданной длины n
	dataInput(input, n);
	res = findNumbers(n);
	dataOutput(output, res);
	fclose(input);
	fclose(output);
	return 0;
}