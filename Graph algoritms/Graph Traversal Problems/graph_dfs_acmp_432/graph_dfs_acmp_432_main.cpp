// Прямоугольный садовый участок шириной N и длиной M метров разбит на квадраты со стороной 1 метр.
// На этом участке вскопаны грядки. Грядкой называется совокупность квадратов, удовлетворяющая таким условиям:
//	- из любого квадрата этой грядки можно попасть в любой другой квадрат этой же грядки, последовательно переходя по грядке из квадрата в квадрат через их общую сторону;
//	- никакие две грядки не пересекаются и не касаются друг друга ни по вертикальной, ни по горизонтальной сторонам квадратов(касание грядок углами квадратов допускается).
// Подсчитайте количество грядок на садовом участке.

#include <iostream>
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::stack;

const int max_len = 202;
char field[max_len][max_len];

struct coord //координаты задаем: x - по вертикали, y - по горизонтали
{
	int x;
	int y;
};

void input_data(int &height, int &width, char field[][max_len])
{
	cin >> height >> width;
	for (int i = 1; i <= height; ++i)
		for (int j = 1; j <= width; ++j){
			cin >> field[i][j];
		}
}

void check_up(coord crd, char field[max_len][max_len], stack <coord> &s)
{
	if (field[crd.x - 1][crd.y] == '#'){
		coord t = { crd.x - 1, crd.y };
		s.push(t);
	}
}


void check_right(coord crd, char field[max_len][max_len], stack <coord> &s)
{
	if (field[crd.x][crd.y + 1] == '#'){
		coord t = { crd.x, crd.y + 1 };
		s.push(t);
	}
}

void check_down(coord crd, char field[max_len][max_len], stack <coord> &s)
{
	if (field[crd.x + 1][crd.y] == '#'){
		coord t = { crd.x + 1, crd.y };
		s.push(t);
	}
}

void check_left(coord crd, char field[max_len][max_len], stack <coord> &s)
{
	if (field[crd.x][crd.y - 1] == '#'){
		coord t = { crd.x, crd.y - 1 };
		s.push(t);
	}
}

int dfs_bed_finder(int &height, int &width, char field[][max_len])
{
	stack <coord> s;
	int count = 0;
	coord crd;
	for (int i = 1; i <= height; ++i)
		for (int j = 1; j <= width; ++j){
			crd = { i, j }; //coordinate
			if (field[crd.x][crd.y] == '#'){
				++count;
				s.push(crd);
				while (!s.empty()){
					crd = s.top();
					s.pop();
					field[crd.x][crd.y] = '.';
					check_up(crd, field, s);
					check_right(crd, field, s);
					check_down(crd, field, s);
					check_left(crd, field, s);
				}
			}
		}
	return count;
}

int main()
{
	int height, width;
	input_data(height, width, field);
	int bed_qty = dfs_bed_finder(height, width, field);
	cout << bed_qty;
	return 0;
}