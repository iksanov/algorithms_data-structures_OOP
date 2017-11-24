#include <iostream>
#include <queue>
using std::queue;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;
ifstream fin("input.txt");
ofstream fout("output.txt");



const int max_len = 20;
int field[max_len][max_len];

struct Coord
{
	int x;
	int y;
};

void step(Coord v, int dx, int dy, int length, int field[max_len][max_len], queue <Coord> &q)
{
	if (((v.x + dx >= 0) && (v.y + dy >= 0) && (v.x + dx < length) && (v.y + dy < length) && field[v.x + dx][v.y + dy] == 0)){
		field[v.x + dx][v.y + dy] = field[v.x][v.y] + 1;
		Coord t = { v.x + dx, v.y + dy };
		q.push(t);
	}
}

int bfs_route(Coord a, Coord finish, int length, int field[max_len][max_len]) //�� ����: ���������� ��������� �����, ������ ������� ������� (n x n), �������-�����, ������ marked (����������)
{
	queue <Coord> q;
	q.push(a);
	field[a.x][a.y] = 1; //����� 1, � �� 0, ������ ��� ��� ������ ����� �������� ������, � �� ������� ������������� ��� (-1). ������� � ����� �� ���� ������ ������ 1.
	while (!q.empty()){
		Coord v = q.front(); //��������� ������ ������� �������
		q.pop();
		//��������� �� ���� ������ ������� � ������ ��� ���������, �������� �� �� ������ ��� �� �����
		step(v, -2, 1, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
		step(v, -1, 2, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
		step(v, 1, 2, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
		step(v, 2, 1, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
		step(v, 2, -1, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
		step(v, 1, -2, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
		step(v, -1, -2, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
		step(v, -1, -2, length, field, q);
		if (field[finish.x][finish.y] != 0)
			return field[finish.x][finish.y];
	}
}

int main()
{
	int length;
	fin >> length;
	Coord start = { 0, 0 };
	Coord finish = { 0, 0 };
	fin >> start.x >> start.y;
	fin >> finish.x >> finish.y;
	--start.x;
	--start.y;
	--finish.x;
	--finish.y;
	int res = bfs_route(start, finish, length, field) - 1;
	fout << res;

	fin.close();
	fout.close();

	return 0;
}