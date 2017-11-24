#include <iostream>
using std::cout;
using std::endl;

struct Vector2D
{
	double x, y;
	explicit Vector2D(double x_ = 0, double y_ = 0) //запрещает использовать конструктор для всякого неявного преобразования типов
	{
		x = x_;
		y = y_;
		cout << "Vector2D (double, double)\n";
	}

	Vector2D operator+(const Vector2D& v) ///////////////почему если поставить &, то не работает с несколькими переменными, а должно быть наоборот
	{
		return Vector2D(x + v.x, y + v.y);
	}

	Vector2D operator-(const Vector2D& v)
	{
		return  Vector2D(x - v.x, y - v.y);
	}

	double operator*(const Vector2D& v) //скалярное произвдение
	{
		return  (x * v.x + y * v.y);
	}

	Vector2D operator*(double k) const //умножение вектора на число
	{
		return Vector2D(x * k, y * k);
	}

	Vector2D operator/(double k)
	{
		return Vector2D(x / k, y / k);
	}

	Vector2D operator+=(const Vector2D& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2D operator-=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2D operator/=(double k)
	{
		x /= k;
		y /= k;
		return *this;
	}

	bool operator==(const Vector2D& v)
	{
		bool t;
		if ((x == v.x) && (y == v.y)) t = true; else t = false;
		return t;
	}
};

Vector2D operator*(double k, const Vector2D& v)
{
	return v*k;
}

std::ostream& operator<<(std::ostream& s, const Vector2D& v)
{
	s << "(" << v.x << "," << v.y << ")";
	return s;
}

int main()
{
	Vector2D v1(1, 2);
	Vector2D v2(3, 4);
	Vector2D v3(5, 6);
	Vector2D v4(7, 8);
	bool t = true;
	if (v1 == v2) t == true; else t = false;
	cout << v1 << v2 << v3 << v4 << endl;
	return 0;
}