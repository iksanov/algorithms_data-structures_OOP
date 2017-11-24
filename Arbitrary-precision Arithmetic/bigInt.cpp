#include "bigInt.h"
#include <iostream>
#include <fstream>
#include <vector>
using std::vector;

BigInt::BigInt(int num) //констурктор по числу
{
	if (num >= 0)
		sign = 1;
	else{
		sign = -1;
		num *= -1;
	}
	if (num == 0)
		digits.push_back(0);
	while (num > 0){
		digits.push_back(num % 10);
		num = num / 10;
	}
}

BigInt::BigInt(const string &str)
{
	int len = str.length();
	if (str[0] == '-'){
		sign = -1;
		digits.resize(len - 1);
	}
	else{
		if (str[0] == '+'){
			sign = 1;
			digits.resize(len - 1);
		}
		else{
			sign = 1;
			digits.resize(len);
			digits[len - 1] = str[0] - '0';
		}
	}

	for (int i = 0; i < len - 1; ++i){
		digits[i] = str[len - i - 1] - '0';
	}
}

BigInt::BigInt(vector <int> v, int s) //конструктор по вектору и знаку
{
	sign = s;
	for (unsigned i = 0; i < v.size(); ++i)
		digits.push_back(v[i]);
}

BigInt::BigInt(const BigInt& n)
{
	*this = BigInt(n.digits, n.sign);
}

BigInt& BigInt::operator=(const BigInt& n)
{
	digits = n.digits;
	sign = n.sign;
	return *this;
}

bool BigInt::operator>(const BigInt& n) const
{
	int len = digits.size(); //для удобства и избежания длинных выражений
	int nlen = n.digits.size(); //для удобства и избежания длинных выражений
	if (sign == 1 && n.sign == -1)
		return true;
	if (sign == -1 && n.sign == 1)
		return false;
	if (sign == -1 && n.sign == -1)
		return !(BigInt(digits,1) > BigInt(n.digits, 1));
	if (len > nlen){
		return true;
	}
	else{
		if (len == nlen){ //определяем какое число больше, чтобы определить знак результата
			for (int i = len - 1; i >= 0; --i){
				if (digits[i] == n.digits[i])
					continue;
				else
					if (digits[i] > n.digits[i])
						return true;
					else
						return false;
			}
			return false;
		}
		else{ //если оказалось в итоге, что len < nlen
			return false;
		}
	}

}

bool BigInt::operator==(const BigInt& n) const
{
	if (*this > n || n > *this)
		return false;
	return true;
}

BigInt BigInt::operator+(const BigInt& n) const
{
	vector <int> b_tmp; //big tmp
	vector <int> s_tmp; //small tmp
	if (digits.size() > n.digits.size()){
		b_tmp = digits;
		s_tmp = n.digits;
	}
	else{
		b_tmp = n.digits;
		s_tmp = digits;
	}
	int extra = 0; //один в уме
	unsigned pos = 0; //текущий разряд (позиция) при прохождении по циклу
	for (; pos < s_tmp.size(); ++pos){ //складываем цифры из двух векторов
		b_tmp[pos] += (s_tmp[pos] + extra);
		extra = b_tmp[pos] / 10; //если есть переход через десяток, то запомним один в уме
		b_tmp[pos] %= 10; //этим действием уберем лишнюю единичку в этой ячейке в случае перехода через десяток
	}
	for (; pos < b_tmp.size() && extra; ++pos){ //проходимся до тех пор, пока не исчезнет один в уме
		b_tmp[pos] += extra;
		extra = b_tmp[pos] / 10; //если есть переход через десяток, то запомним один в уме
		b_tmp[pos] %= 10; //этим действием уберем лишнюю единичку в этой ячейке в случае перехода через десяток
	}
	if (extra == 1){ //если один в уме еще остался, то создадим последний разряд и добавим в него единичку
		b_tmp.push_back(1);
	}
	return BigInt(b_tmp, 1);
}

BigInt BigInt::operator-(const BigInt& n) const
{
	vector <int> b_tmp; //big tmp
	vector <int> s_tmp; //small tmp
	int tmp_sign = 1;
	int extra = 0; //один в уме
	unsigned pos = 0; //текущий разряд (позиция) при прохождении по циклу
	b_tmp = digits;
	s_tmp = n.digits;

	if (n > *this){ //определяем какое число больше, чтобы определить знак результата
		tmp_sign = -1;
		b_tmp = n.digits;
		s_tmp = digits;
	}	
	for (; pos < s_tmp.size(); ++pos){
		b_tmp[pos] -= s_tmp[pos] + extra - 10; //вычитаем цифры из двух векторов, учитывая один в уме и, на всякий случай, заранее занимая десяток из следующего разряда
		if (b_tmp[pos] < 10){ //проверяем, был ли преход через десяток
			extra = 1;
		}
		else{
			extra = 0;
			b_tmp[pos] %= 10; // если не было, то отсекаем лишнюю первую единичку в текущей ячейке
		}
	}
	for (; pos < b_tmp.size() && extra; ++pos){ //проходимся до тех пор, пока не исчезнет один в уме
		b_tmp[pos] -= extra - 10; //вычитаем цифры из двух векторов, учитывая один в уме и, на всякий случай, заранее занимая десяток из следующего разряда
		if (b_tmp[pos] < 10){ //проверяем, был ли преход через десяток
			extra = 1;
		}
		else{
			extra = 0;
			b_tmp[pos] %= 10; // если не было, то отсекаем лишнюю первую единичку в текущей ячейке
		}
	}
	while (b_tmp[b_tmp.size() - 1] == 0 && b_tmp.size() != 1) //если появился первый незначащий ноль (и это не есть ответ) - мы его уберем
		b_tmp.pop_back();
	return BigInt(b_tmp, tmp_sign);
}

BigInt BigInt::operator*(const BigInt& n) const
{
	int len = digits.size();
	int nlen = n.digits.size();
	if (digits[0] == 0 && len == 1 || n.digits[0] == 0 && nlen == 1)
		return BigInt(0);
	vector <int> tmp(nlen + len);
	for (int i = 0; i < len; ++i) //сложим числа столбиком
		for (int j = 0; j < nlen; ++j)
			tmp[i + j] += digits[i] * n.digits[j];

	for (int i = 0; i < nlen + len - 1; ++i)
	{
		tmp[i + 1] += tmp[i] / 10; //перекинем лишние десятки в следующий разряд
		tmp[i] %= 10; //отсечем лишние десятки
	}
	if (tmp[tmp.size() - 1] == 0) //если первый незначащий ноль так и остался - мы его уберем
		tmp.pop_back();
	return BigInt(tmp, 1);
}

BigInt BigInt :: operator / (const BigInt& other) const{
	vector<int> dig = other.getNumber();
	if (other > (*this)) {
		return BigInt(0);
	}
	int result_size;
	int flag = 0;
	for (int i = 1; i <= dig.size(); i++) {
		if (digits[digits.size() - i] > dig[dig.size() - i]) {
			result_size = result_size = digits.size() - dig.size() + 1;
			flag = 1;
			break;
		}
		else if (digits[digits.size() - i] < dig[dig.size() - i]) {
			result_size = digits.size() - dig.size();
			flag = 1;
		}
	}
	if (!flag) {
		result_size = digits.size() - dig.size() + 1;
	}
	vector<int> result(result_size);
	BigInt compare(0);
	for (int i = result_size - 1; i >= 0; i--) {
		int j = 0;
		for (; j < 10; ++j) {
			result[i] = j;
			compare = BigInt(result, 1);
			if ((compare * other) > *this) {
				break;
			}
		}

		result[i] = j - 1;
	}
	compare = BigInt(result, 1);
	return compare;
}

int BigInt::get_size() const
{
	return digits.size();
}

vector<int> BigInt::getNumber() const {
	return digits;
}

ostream& operator<<(ostream& out, const BigInt& n)
{
	if (n.sign == -1)
		out << '-';
	for (int i = n.get_size() - 1; i >= 0; --i)
		out << n.digits[i];
	return out;
}

int degree(int num, int exp)
{
	int res = 1;
	for (int i = 0; i < exp; ++i)
		res *= num;
	return res;
}