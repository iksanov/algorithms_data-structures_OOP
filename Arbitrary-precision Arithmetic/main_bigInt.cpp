#include "bigInt.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::ofstream;

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");

	string a; //выводит кучу нулей
	string b;
	fin >> a >> b;

		
	fout << BigInt(a) - BigInt(b);

	fin.close();
	fout.close();
	return 0;
}