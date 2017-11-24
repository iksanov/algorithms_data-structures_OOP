#include "stack.h"
#include <iostream>
#include <exception>
using std::cin;
using std::cout;
using std::endl;

//���� ���������� ����� ��� ������, �� ��������� ����� ����������� � ������� ������, � ���� ������, �� ��������� ����������� ����������� � ����� ������ ����� �����
void print_and_pop(Stack &s, int n) //��������� �� ����: ����� � ���������� ���������, ������� ����� �������� �� ����� � ����������
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << s.pop() << endl;
	cout << endl;
}

int main()
{
	try{
		cout << "start\n"; //������������� � ������ ������
		Stack st(23);
		int n;
		do{
			cin >> n;
			st.push(n);
		} while (n >= 0); //������������ ���� ������������� ������
		st.pop(); //������� ������������� ����� �� �����

		int m = 1;
		print_and_pop(st, m); //������� ������� ��� m �����

		cout << "size = " << st.size() << endl;
		while (st.size() > 0) //������� ���������� �������� �����
			cout << st.pop() << "\n";
		cout << "finish\n"; //������������� � ����� ������
		return 0;
	}
	catch (const std::exception &e){
		cout << "Exception occurred: " << e.what() << endl;
	}
}