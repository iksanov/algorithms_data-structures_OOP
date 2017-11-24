#include <algorithm>
#include <time.h>
#include "generateRandomArray.h"

int random(int from, int to)
{
	srand(time(0));
	int tmp = from + rand() % (to - from + 1);
	return tmp;
}
void generateArray(int* array, int length)
{
	for (int i = 0; i < length; i++) array[i] = i;
}
void randomizeArray(int* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		int tmp = random(0, length - 1);
		std::swap(array[i], array[tmp]);
	}
}
void generateRandomArray(int* array, int length)
{
	generateArray(array, length);
	randomizeArray(array, length);
}