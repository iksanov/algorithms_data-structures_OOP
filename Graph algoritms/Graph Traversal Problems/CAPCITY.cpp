#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <algorithm>
using std::vector;
using std::sort;

vector <vector <int>> graph;
vector <vector <int>> reversed_graph;
vector <bool> arr_cities; //отмечаем посещенные города
vector <int> capitals; //массив подходящих столиц

void input_data(int &cities, int &roads)
{
	scanf("%d %d", &cities, &roads);
	graph.resize(cities);
	reversed_graph.resize(cities);
	int from = 0;
	int to = 0;
	for (int i = 0; i < roads; ++i){
		scanf("%d %d", &from, &to);
		graph[from-1].push_back(to-1);
		reversed_graph[to-1].push_back(from-1);
	}
}

void reversed_dfs(int city, int &count) //будет считать, сколько вершин мы обошли в сount
{
	arr_cities[city] = true;
	for (int i = 0; i < reversed_graph[city].size(); ++i)
		if (arr_cities[reversed_graph[city][i]] == false){
			++count;
			reversed_dfs(reversed_graph[city][i], count);
		}
}

void capitals_dfs(int city)
{
	arr_cities[city] = true;
	for (int i = 0; i < graph[city].size(); ++i)
		if (arr_cities[graph[city][i]] == false){
			capitals.push_back(graph[city][i]);
			capitals_dfs(graph[city][i]);
		}
}

int main()
{
	int qty_cities = 0;
	int qty_roads = 0;
	int count = 0; //считает сколько городов мы обошли в цикле dfs
	input_data(qty_cities, qty_roads);
	
	for (int i = 0; i < qty_cities; ++i){
		count = 1;
		arr_cities.assign(qty_cities, false);
		reversed_dfs(i, count);
		if (count == qty_cities){
			capitals.push_back(i);	
			break;
		}
	}

	arr_cities.assign(qty_cities, false);
	int first_capital = capitals[0];
	capitals_dfs(first_capital);

	printf("%d\n", capitals.size());
	sort(capitals.begin(), capitals.end());
	for (vector<int>::iterator it = capitals.begin(); it != capitals.end(); ++it){ //прибавляем единицу к каждому обратно, чтобы вывести в первоначальном виде
		printf("%d ", *it + 1);
	}
	return 0;
}
