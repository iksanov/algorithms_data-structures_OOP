#include <iostream>
using namespace std;
bool flag = true;
int n;
const int max_n = 100;
int marked[max_n];
int graph[max_n][max_n];

void dfs(int v){
	marked[v] = 1;
	for (int i = 0; i < n; i++){
		if (graph[v][i]) {
			if (!marked[i]) {
				dfs(i);
				if (!flag)
					return;
			}
			else if (marked[i] == 1){
				flag = false;
				return;
			}
		}
	}
	marked[v] = 2;
}

int main()
{
	int m, a, b;
	cin >> n >> m;
	for (int i = 0; i< m; i++){
		cin >> a >> b;
		graph[a - 1][b - 1] = 1;
	}
	for (int i = 0; i < n; i++)
		if (!marked[i])
			dfs(i);
	if (flag) {
		cout << "Yes" << endl;

	}
	else
		cout << "No" << endl;
	return 0;
}