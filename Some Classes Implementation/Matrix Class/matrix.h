#pragma once
#include <ostream>
class Matrix
{
public:
	Matrix(int rows_ = 3, int cols_ = 3);
	Matrix(const Matrix&);
	~Matrix();
	int height() const;
	int width() const;
	int& operator() (int, int);
	int operator()(int x, int y) const;
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix& m);
	Matrix operator+(const Matrix&) const;
	Matrix& operator*=(const Matrix& m);
	Matrix operator*(const Matrix& m) const;
	Matrix& transpose();
private:
	int* arr;
	int rows;
	int cols;
};
Matrix operator* (int num, const Matrix& m);
std::ostream& operator<< (std::ostream& out, const Matrix& m);