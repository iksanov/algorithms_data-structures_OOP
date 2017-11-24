#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "matrix.h"
#include <iostream>
#include <exception>

using std::cout;
using std::endl;

class AutoLeakChecker
{
public:
	~AutoLeakChecker()
	{
		_CrtDumpMemoryLeaks();
	}
} global_leak_checker;

int main()
{
	try{
		Matrix v(1, 10); // вектор 1x10, инициализирован нулями
		for (int i = 0; i < 10; ++i)
			v(0, i) = i;
		cout << v << endl;
		Matrix a(2, 3); // матрица 2x3, инициализирована нулями
		for (int i = 0; i < a.height(); ++i)
			for (int j = 0; j < a.width(); ++j)
				a(i, j) = i + 3 * j;
		cout << a << endl;  // [ 0 3 6
							//   1 4 7 ]

		const Matrix c = a;

		cout << c + 2 * a << endl;	// [ 0 9 18
									//   3 12 21 ]
		cout << c(1, 1) << endl; // 4
		cout << c << endl;
		a = Matrix(10, 20); // инициализирована нулями //здесь была УТЕЧКА памяти. Решение: при присваивании нужно сначала удалить старый массив arr, который создается при конструкторе, а потом создать новый вместо него.
		v *= a; // v умножился на a справа, v = v * a
		v.transpose(); // v стал вектором 10x1 (транспонировался)
		cout << a.height() << "x" << a.width() << endl; // 10x20

//exception part

		//a(100, 100);
		//a = Matrix(10, 20); // инициализирована нулями
		//a += c;

		Matrix e(3, 3);
		Matrix k(3, 3);
		for (int i = 0; i < 3; i++)
			e(i, i) = 1;
		for (int i = 0; i < 3; i++)
			k(i, i) = i+1;
		e *= k;
		cout << e;
		return 0;
	}
	catch (const std::exception &e){
		cout << "Exception: " << e.what() << endl;
	}
}