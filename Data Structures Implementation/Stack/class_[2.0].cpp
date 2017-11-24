#include "stack.h"
#include <iostream>
#include <exception>
using std::cin;
using std::cout;
using std::endl;

//если передавать класс как ссылку, то изменения будут происходить в текущем классе, а если просто, то вызовется конструктор копирования и будет создан новый класс
void print_and_pop(Stack &s, int n) //принимает на вход: класс и количество элементов, которые нужно вытащить из стека и напечатать
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << s.pop() << endl;
	cout << endl;
}

int main()
{
	try{
		cout << "start\n"; //сигнализируем о начале работы
		Stack st(23);
		int n;
		do{
			cin >> n;
			st.push(n);
		} while (n >= 0); //ограничиваем ввод отрицательным числом
		st.pop(); //убираем отрицательное число из стека

		int m = 1;
		print_and_pop(st, m); //вызовем функцию для m чисел

		cout << "size = " << st.size() << endl;
		while (st.size() > 0) //выведем оставшиеся элементы стека
			cout << st.pop() << "\n";
		cout << "finish\n"; //сигнализируем о конце работы
		return 0;
	}
	catch (const std::exception &e){
		cout << "Exception occurred: " << e.what() << endl;
	}
}