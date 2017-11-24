#include <fstream>
#include <queue>
using std::ifstream;
using std::ofstream;
using std::queue;
using std::endl;

const int len = 42;
char g[len][len]; // cоздаем массив глобально, тогда он сразу инициализирован нулями, и мы не тратим на это время. И не придется постоянно переаллоцировать его, так как N <= 100
int m[len][len]; // cоздаем массив marked - кого мы уже добавили в очередь, а также в нем будем хранить длину пути

struct coord{ //координаты задаем: x - по вертикали, y - по горизонтали
	int x;
	int y;
};

void step_up(coord v, int m[len][len], char g[len][len], queue <coord> &q)
{
	if ((g[v.x - 1][v.y] == '.' || g[v.x - 1][v.y] == 'X') && (!m[v.x - 1][v.y])){
		m[v.x - 1][v.y] = m[v.x][v.y] + 1;
		coord t = { v.x - 1, v.y };
		q.push(t);
	}
}


void step_right(coord v, int m[len][len], char g[len][len], queue <coord> &q)
{
	if ((g[v.x][v.y + 1] == '.' || g[v.x][v.y + 1] == 'X') && (!m[v.x][v.y + 1])){
		m[v.x][v.y + 1] = m[v.x][v.y] + 1;
		coord t = { v.x, v.y + 1 };
		q.push(t);
	}
}

void step_down(coord v, int m[len][len], char g[len][len], queue <coord> &q)
{
	if ((g[v.x + 1][v.y] == '.' || g[v.x + 1][v.y] == 'X') && (!m[v.x + 1][v.y])){
		m[v.x + 1][v.y] = m[v.x][v.y] + 1;
		coord t = { v.x + 1, v.y };
		q.push(t);
	}
}

void step_left(coord v, int m[len][len], char g[len][len], queue <coord> &q)
{
	if ((g[v.x][v.y - 1] == '.' || g[v.x][v.y - 1] == 'X') && (!m[v.x][v.y - 1])){
		m[v.x][v.y - 1] = m[v.x][v.y] + 1;
		coord t = { v.x, v.y - 1 };
		q.push(t);
	}
}

void bfs_route(coord a, int n, char g[len][len], int m[len][len]) //на вход: координаты стартовой точки, размер стороны таблицы (n x n), таблица-карта, массив marked (помеченных)
{
	queue <coord> q;
	q.push(a);
	m[a.x][a.y] = 1; //пишем 1, а не 0, потому что наш массив сразу заполнен нулями, и не хочется перезаполнять его (-1). Поэтому в конце их пути просто вычтем 1.
	while (!q.empty()){
		coord v = q.front(); //извлекаем первый элемент очереди
		q.pop();
		//пробегаем по всем четырем соседям и каждый раз проверяем, есть ли там сосед, и отмечали ли мы его до этого
		step_up(v, m, g, q);
		step_right(v, m, g, q);
		step_down(v, m, g, q);
		step_left(v, m, g, q);
	}
}

bool plus_up(coord &v, int m[len][len], char g[len][len]) //функции булевы, чтобы проверять выполнилась она или нет
{
	if ((m[v.x - 1][v.y] == m[v.x][v.y] - 1)){
		g[v.x - 1][v.y] = '+';
		v = { v.x - 1, v.y };
		return true;
	}
	return false;
}

bool plus_right(coord &v, int m[len][len], char g[len][len])
{
	if ((m[v.x][v.y + 1] == m[v.x][v.y] - 1)){
		g[v.x][v.y + 1] = '+';
		v = { v.x, v.y + 1 };
		return true;
	}
	return false;
}

bool plus_down(coord &v, int m[len][len], char g[len][len])
{
	if ((m[v.x + 1][v.y] == m[v.x][v.y] - 1)){
		g[v.x + 1][v.y] = '+';
		v = { v.x + 1, v.y };
		return true;
	}
	return false;
}

bool plus_left(coord &v, int m[len][len], char g[len][len])
{
	if ((m[v.x][v.y - 1] == m[v.x][v.y] - 1)){
		g[v.x][v.y - 1] = '+';
		v = { v.x, v.y - 1 };
		return true;
	}
	return false;
}

void prepare_for_print(coord v, int n, int m[len][len], char g[len][len])
{
	g[v.x][v.y] = '+';
	int res = m[v.x][v.y] - 1;
	for (int i = res-1; i > 0; --i){ //вычитаем из res 1, так как проплюсовывать будем на одну клетку меньше, так как в последней (стартовой) оставляем @
		!plus_up(v, m, g) && !plus_right(v, m, g) && !plus_down(v, m, g) && !plus_left(v, m, g);
	}
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");

	int n; //количество элементов
	fin >> n;
	coord a; //координаты начала пути
	coord b; //координаты конца пути
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j){
			fin >> g[i][j];
			if (g[i][j] == '@'){ //находим точку старта
				a.x = i;
				a.y = j;
			}
			if (g[i][j] == 'X'){ //находим точку финиша
				b.x = i;
				b.y = j;
			}
		}
	for (int i = 0; i <= n + 1; ++i){ //обнесли наш массив g препятствиями с краев
		g[i][0] = 'O';
		g[i][n + 1] = 'O';
		g[0][i] = 'O';
		g[n+1][i] = 'O';

	}

	bfs_route(a, n, g, m);
	if (m[b.x][b.y] == 0)
		fout << "No" << endl;
	else{
		fout << "Yes" << endl;
		prepare_for_print(b, n, m, g);
		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= n; ++j)
				fout << g[i][j];
			fout << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
}