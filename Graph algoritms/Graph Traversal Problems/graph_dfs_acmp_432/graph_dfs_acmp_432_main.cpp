// ������������� ������� ������� ������� N � ������ M ������ ������ �� �������� �� �������� 1 ����.
// �� ���� ������� �������� ������. ������� ���������� ������������ ���������, ��������������� ����� ��������:
//	- �� ������ �������� ���� ������ ����� ������� � ����� ������ ������� ���� �� ������, ��������������� �������� �� ������ �� �������� � ������� ����� �� ����� �������;
//	- ������� ��� ������ �� ������������ � �� �������� ���� ����� �� �� ������������, �� �� �������������� �������� ���������(������� ������ ������ ��������� �����������).
// ����������� ���������� ������ �� ������� �������.

#include <iostream>
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::stack;

const int max_len = 202;
char field[max_len][max_len];

struct coord //���������� ������: x - �� ���������, y - �� �����������
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