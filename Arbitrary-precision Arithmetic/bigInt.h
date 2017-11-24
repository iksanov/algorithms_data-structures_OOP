#pragma once
#include <vector>
using std::vector;
using std::string;
using std::ostream;
using std::ofstream;


class BigInt
{
public:
	BigInt(int);
	BigInt(const string&);
	BigInt(vector <int> v, int s);
	BigInt(const BigInt&);
	bool operator>(const BigInt& n) const;
	bool operator==(const BigInt& n) const;
	BigInt operator+(const BigInt&) const;
	BigInt operator-(const BigInt&) const;
	BigInt operator*(const BigInt&) const;
	BigInt operator/(const BigInt&) const;
	BigInt& operator=(const BigInt&);
	int get_size() const;
	vector<int> getNumber() const;
	friend ostream& operator<<(ostream&, const BigInt&);
private:
	vector <int> digits;
	int sign;
};

int degree(int num, int exp);