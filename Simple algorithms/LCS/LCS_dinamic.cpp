#include "matrix.h"
void lscOut(char* X, char* Z, matrix<char>&b, int nx, int ny, int l)
{
	if (nx == 0 || ny == 0) return;
	if (b(nx, ny) == 0){	// стрелка такая -->  '\'
		lscOut(X, Z, b, nx - 1, ny - 1, l);
		Z[l++] = X[nx - 1];
	}
	else
		if (b(nx, ny) == 1) // стрелка такая '<--'
			lscOut(X, Z, b, nx - 1, ny, l);
		else // стрелка такая '|'
			lscOut(X, Z, b, nx, ny - 1, l);
}
int lcsBuild(char* X, int nx, char* Y, int ny, char* Z)
{
	auto c = matrix <int>(nx + 1, ny + 1);
	auto b = matrix <char>(nx + 1, ny + 1);
	for (int x = 0; x <= nx; x++) c(x, 0) = 0;
	for (int y = 0; y <= ny; y++) c(0, y) = 0;
	for (int y = 1; y <= ny; y++){
		for (int x = 1; x <= nx; x++){
			if (X[x - 1] == Y[y - 1]){
				c(x, y) = c(x - 1, y - 1) + 1;
				b(x, y) = 0; // стрелка такая -->  '\'
			}
			else{
				if (c(x - 1, y) >= c(x, y - 1)){
					c(x, y) = c(x - 1, y);
					b(x, y) = 1; // стрелка такая '<--'
				}
				else {
					c(x, y) = c(x, y - 1);
					b(x, y) = 2; // стрелка такая '|'				
				}
			}
		}
	}
	int l = 0;
	lscOut(X, Z, b, nx, ny, l);
	Z[l] = 0;
	return l;
}

int main()
{
	char Z[20];
}