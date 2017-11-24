using namespace std;
#include "matrix.h"
#include <algorithm>
void knap01Result(matrix<int>&A, int* W, int x, int y, int* R, int &l)// передаем по ссылке то, что хотим изменить, и матрицу, потому что не хотим ее копировать
{
	if (A(x, y) == 0) return;
	if (A(x, y - 1) == A(x, y))
		knap01Result(A, W, x, y - 1, R, l);
	else{
		knap01Result(A, W, x - W[y], y - 1, R, l);
		R[l++] = y;
	}
}
int knap01Solve(int* V, int* W, int n, int wMax, int* R){ //результирующий массив индексов предеметов ( в нем стоят 0/1 ), которые мы кладем в рюкзак
	auto A = matrix<int>(wMax + 1, n + 1); //размер на 1 больше, так как присутствует нулевая строка
	for (int y = 0; y <= n; y++) A(0, y) = 0;
	for (int x = 0; x <= wMax; x++) A(x, 0) = 0;
	for (int y = 1; y <= n; y++){
		for (int x = 1; x <= wMax; x++){
			if (x >= W[y]){
				A(x, y) = max(A(x, y - 1), A(x - W[y], y - 1) + V[y]);
			}
			else{
				A(x, y) = A(x, y - 1);
			}
		}
	}
	int nRes = 0;
	knap01Result(A, W, wMax, n, R, nRes);
	return nRes;
}

void knapsack01()
{
	int W[] = { 0, 1, 2, 3 };
	int V[] {0, 6, 10, 12};
	int R[6]{0};
	const int n{ sizeof(W) / sizeof(*W) };
	int wMax{ 5 };
	int l = knap01Solve(V, W, n - 1, wMax, R);
}

int main()
{
	
	knapsack01();
	return 0;
}
