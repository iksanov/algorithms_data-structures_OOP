#include <iostream>
using namespace std;

int n;
const int max_n = 100;
int a[max_n][max_n];
int marked[max_n];
int sum;
int flag = 1;
void dfs(int i, int prev){
	marked[i] = 1;
	for (int j = 0; j < n; j++){
		if (a[i][j] && j != prev) {
			if (marked[j] == 0){
				dfs(j, i);
			}
			else{
				flag = -1;
				return;
			}
		}
	}
}

int main(){
	cin >> n;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}
	dfs(0, -1);
	if (flag == -1){
		cout << "NO";
		return 0;
	}
	else{
		for (int i = 0; i < n; i++){
			if (marked[i] == 0){
				cout << "NO";
				return 0;
			}
		}
		cout << "YES";
	}
	return 0;
}