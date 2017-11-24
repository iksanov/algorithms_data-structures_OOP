template <typename T>
class matrix{ //класс для сооздания матриц
	int nx; //number of x (столбцов)
	int ny; //кол-во строк
	T* m; //заменили во всем кодe int на некоторый T
public:
	matrix(int nx, int ny) :nx(nx), ny(ny)
	{
		m = new T[nx*ny];
	}

/*
{
	matrix m(10,10);
	for (int y = 0; y < m.rows();y++)
		for (int x = 0;x<m.cols();x++)
			m(x,y)=x+y;
}
*/

	~matrix(){ delete[]m; } //деструктор
	int cols(){ return nx; }
	int rows(){ return ny; }

	T& operator() (int x, int y)
	{
		return m[nx*y + x];
	}
};

/*
{
matrix <int> m1(1,1)
matrix <double> m2(2,2)
matrix <Point> m3(3,3)
 }
 */