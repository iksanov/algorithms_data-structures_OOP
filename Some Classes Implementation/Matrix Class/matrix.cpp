#include "matrix.h"
#include <new>
#include <iostream>
#include <algorithm>
#include <stdexcept>
using std::runtime_error;
using std::cout;
using std::endl;

Matrix::Matrix(int rows_, int cols_)
{
	arr = new int[rows_*cols_];
	for (int i = 0; i < rows_*cols_; ++i)
		arr[i] = 0; //зануляем массив
	rows = rows_;
	cols = cols_;
}
//нельзя просто написать *this = m; потому что в операторе присваивания (для избежания утечек памяти) сначала удаляется старый массив, потом пишется новый. А в этом случае - удалять еще будет нечего, потому что еще не успели ничего создать (new). Будет возникать ошибка
//поэтому пишем тоже самое, что и для оператора присванивания, но без удаления в начале массива (delete[])
Matrix::Matrix(const Matrix& m)
{
	rows = m.rows;
	cols = m.cols;
	arr = new int[rows*cols];
	memcpy(arr, m.arr, sizeof(int)*(rows*cols));
}
Matrix::~Matrix()
{
	delete[] arr;
}
int Matrix::height() const
{
	return rows;
}
int Matrix::width() const
{
	return cols;
}
int& Matrix::operator()(int x, int y) //для левостороннего значения
{
	if (x > rows || y > cols) throw runtime_error("invalid index");
	return arr[x * cols + y];
}

int Matrix::operator()(int x, int y) const //например для печати или правогостороннего значения
{
	if (x > rows || y > cols) throw runtime_error("invalid index");
	return arr[x * cols + y];
}

Matrix& Matrix::operator=(const Matrix& m)
{
	rows = m.rows;
	cols = m.cols;
	delete[] arr;
	arr = new int[rows*cols];
	memcpy(arr, m.arr, sizeof(int)*(rows*cols));
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
	if (rows != m.rows || cols != m.cols) throw runtime_error("incompatible argument dimensions");
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			arr[i * cols + j] += m(i, j);
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const
{
	Matrix f(*this);
	f += m;
	return f;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
	Matrix tmp(rows, m.cols);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < m.cols; ++j)
			for (int k = 0; k < cols; ++k)
				tmp(i,j) += arr[i * cols + k]*m(k, j);
	
	int *pp = new int[10];
	*this = tmp;
	return *this;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	Matrix f(*this);
	f *= m;
	return f;
}

Matrix operator*(int num, const Matrix& m)
{
	Matrix n(m);
	for (int i = 0; i < m.height(); ++i)
		for (int j = 0; j < m.width(); ++j)
			n(i, j) *= num;
	return n;
}

Matrix& Matrix::transpose()
{
	Matrix tmp(cols, rows);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			tmp(j, i) = arr[i * cols + j];
	*this = tmp;
	return *this;
}

std::ostream& operator<< (std::ostream& out, const Matrix& m)
{
	out << "[";
	for (int i = 0; i < m.height(); ++i){
		for (int j = 0; j < m.width(); ++j)
			out << " " << m(i, j);
		if (i == m.height() - 1) out << " ]";
		else out << endl << " ";
	}
	return out;
}