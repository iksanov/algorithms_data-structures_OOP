//
//����� �� ������, ��� char* s � ���������� ������� ������ - const?
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <string>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const int init_capacity = 30;

class AutoLeakChecker{
public:
	~AutoLeakChecker()
	{
		_CrtDumpMemoryLeaks();
	}
} global_leak_checker;

class MyString{
public:
	MyString()
	{
		capacity = init_capacity;
		length = 0;
		data = new char[capacity];
		data[0] = 0;
	}

	MyString(const char* s)
	{
		int len_inc = strlen(s) + 1; //length, increased by +1 (� ������ ������������ ����)
		if (len_inc > init_capacity)
			capacity = len_inc * 2;
		else capacity = init_capacity;
		length = strlen(s);
		data = new char[capacity];
		memcpy(data, s, len_inc * sizeof(char));
	}

	MyString(const MyString& s)
	{
		data = 0; //����� ����������� ���� �����-�� �������� ��� data, ��� ��� � ��������� ������������ ���������� delete ��� data - ������ �������� delete ��� ������� �������

		//int len_inc = s.length + 1; //length, increased by +1 (� ������ ������������ ����)
		//capacity = s.capacity;
		//length = s.length;
		//data = new char[capacity];
		//memcpy(data, s.data, len_inc * sizeof(char));

		*this = MyString(s.data); //��� ��������� ���������� ���� - ��������� ���� ����������� ����� ������
	}

	MyString(char s, int len) // ��� ������ �� ��������� ���������� ���������� ��������
	{
		int len_inc = len + 1; //length, increased by +1 (� ������ ������������ ����)
		if (len_inc > init_capacity)
			capacity = len_inc * 2;
		else capacity = init_capacity;
		length = len;
		data = new char[capacity];
		for (int i = 0; i < len; ++i)
			data[i] = s;
	}

	~MyString()
	{
		delete[] data;
	}

	void check_capacity(int len) //��������� ������ �� ������������ ����� �� �������� � ������ (�� ���� ����� �������� ����� ����� ������ - ������������)
	{
		int len_inc = len + 1; //length, increased by +1 (� ������ ������������ ����)
		if (capacity < len_inc){
			capacity = len_inc * 2; // ����� ����� �������� � ������� len * 2
			
			char* tmp = new char[capacity];
			memcpy(tmp, data, sizeof(char) * len_inc);
			delete[] data;
			data = tmp;
		}
	}

	MyString& operator+=(char s)
	{
		int len_inc = length + 1; //length, increased by +1 (� ������ ������������ ����)
		check_capacity(len_inc + 1);
		data[length] = s;
		data[length++] = '\0';
		return *this;
	}

	MyString& operator+=(const char* s)
	{
		int len_inc = strlen(s) + 1; //length, increased by +1 (� ������ ������������ ����)
		check_capacity(length + strlen(s));
		memcpy(data + length, s, len_inc * sizeof(char));
		length += strlen(s);
		return *this;
	}

	MyString& operator+=(const MyString& s)
	{

		return (*this += s.data);

		//int len_inc = s.length + 1; //length, increased by +1 (� ������ ������������ ����)
		//check_capacity(length + s.length);
		//memcpy(data + length, s.data, len_inc * sizeof(char));
		//length += s.length;
		//return *this;
	}

	MyString operator+(char s) const
	{
		MyString tmp = *this; //�� ������ check_capacity, ��� ��� ��� ��������� � ��������� +=
		tmp += s;
		return tmp;
	}

	MyString operator+(const char* s) const
	{
		MyString tmp = *this;
		tmp += s;
		return tmp;
	}

	MyString operator+(const MyString& s) const
	{
		MyString tmp = *this;
		tmp += s;
		return tmp;
	}

	MyString& operator=(const MyString& s) //�������� ������������ ������ ����������� ����� ����������� �����������, ��� ��� ����� �� �������� ������ ������� ���������� ������, ��������� � ��� ����������� ���������� � � ����� ����� ���������� ��������� (��-�� ���� ������������� �������� ��� ����� ���������� ������ ���������) �� ��� ����� ����������, �� ������ �� ����� ��������. ������ ��� ��� ������ �� ������� ���������� ���������� ������ ��� ���������� ������, � ���������, ������� �� ���� �������� - ������ �� �������� ���������
	{
		if (&s == this) return *this;
		capacity = s.capacity;
		length = s.length;
		int len_inc = length + 1; //length, increased by +1 (� ������ ������������ ����)
		delete[] data;
		data = new char[capacity];
		memcpy(data, s.data, len_inc * sizeof(char));
		return *this;
	}

	int get_length() const
	{
		return length;
	}

	char operator[](int n) const //�������� ��� ������ � ����������������� ��������
	{
		return data[n];
	}

	char& operator[](int n) //��� �������������� ��������
	{
		return data[n];
	}

	char* mass_pointer() const //���������� ������������� ��������� �� ������
	{
		return data;
	}

	void reverse()
	{
		int tmp = 0;
		for (int i = 0; i < length / 2; ++i){
			tmp = data[i];
			data[i] = data[length - 1 - i];
			data[length - 1 - i] = tmp;
		}
	}

	friend std::istream& operator>>(std::istream& in, MyString& s);
	friend MyString operator+(char ch, MyString& s);

private:
	char* data;
	int length;
	int capacity;
};
std::ostream& operator<<(std::ostream& out, const MyString& s)
{
	for (int i = 0; i < s.get_length(); ++i)
	{
		out << s[i];
	}
	out << endl;
	return out;
}

std::istream& operator>>(std::istream& in, MyString& s)
{
	in >> s.data;
	s.length = strlen(s.data);
	return in;
}

MyString operator+(char ch, MyString& s) // �������� ��� ��������, ��� ��� ���������� �������� ��� ������, � ������������� *this �� ���������� �� ��������� ��� ���� �� ����������
{
	int len_inc = s.length + 1; //length, increased by +1 (� ������ ������������ ����)
	char* tmp = new char[len_inc + 1];
	tmp[0] = ch;
	memcpy(tmp + 1, s.data, sizeof(char)*len_inc);
	MyString tmp_string(tmp);
	delete[] tmp;
	return tmp_string;
}

MyString foo()
{
	MyString tmp("This is tmp");
	return tmp;
}


int main()
{
	MyString h = "Hello", w("world");
	cout << h + ", " + w + '!' << endl; // Hello, world!
	const MyString c = "I am constant";
	cout << c[0] + MyString(" am good constant\n"); // I am good constant
	cout << c.get_length() << endl; // 13
	h += ", ";
	h += w;
	h += '!';
	cout << h << endl; // Hello, world!
	MyString a;
	a = h = c;
	cout << a << endl; // I am constant
	a[0] = 'i';
	cout << a << endl; // i am constant
	h = "ohio";
	h.reverse();
	cout << h << endl; // oiho
	MyString z('z', 10); // ������� ������ �� 10 ���� z
	cout << z << endl; // zzz�
	cout << "Enter your name: ";
	cin >> h;
	cout << "Hello, " << h << endl;
	return 0;
}