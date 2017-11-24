#pragma once
#include <vector>

struct Edge {
  int begin;
  int end;
  int weight;
  Edge() {}
  Edge(int _begin, int _end, int _weight) : begin(_begin), end(_end), weight(_weight) {}
};

bool comparator(const Edge& edge_1, const Edge& edge_2);

class Graph {
public:
  Graph() = delete;
  explicit Graph(int _num_of_v, const std::vector<Edge>& _vec_of_edges) : num_of_v(_num_of_v), vec_of_edges(_vec_of_edges) { }
  int get_num_of_v() const { return num_of_v; }
  const std::vector<Edge>& get_vec_of_edges() const { return vec_of_edges; }
  void sort_vec_of_edges();
private:
  int num_of_v;
  std::vector<Edge> vec_of_edges;
};

class KruskalMstFinder {
public:
  KruskalMstFinder() = delete;
  explicit KruskalMstFinder(const Graph& _graph) : graph(_graph) {}
  void kruskalAlgo();
  int return_mst_length() const { return mst_length; }
private:
  Graph graph;
  int mst_length = 0;
  std::vector<int> parent;
  std::vector<int> rank = std::vector<int>(graph.get_num_of_v(), 1);
  //optimized method that not only returns parent
  //but rewrites parent of other vertices in this branch by the way to the root of the tree
  int get_parent_otimized(int vertex);
  void unite_sets(int first_vertex, int second_vertex);
};

void input(int& num_of_v, std::vector<Edge>&);

void output(int ans);

void solve();