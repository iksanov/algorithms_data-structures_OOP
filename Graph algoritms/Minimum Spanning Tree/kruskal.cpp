#include "kruskal.h"
#include <algorithm>
#include <fstream>

bool comparator(const Edge& edge_1, const Edge& edge_2) {
  return (edge_1.weight < edge_2.weight);
}

int KruskalMstFinder::get_parent_otimized(int vertex) {
  if (vertex == parent[vertex]) {
    return vertex;
  }
  else {
    return parent[vertex] = get_parent_otimized(parent[vertex]);
  }
}

void KruskalMstFinder::unite_sets(int first_vertex, int second_vertex) {
  if (rank[first_vertex] < rank[second_vertex]) {
    std::swap(first_vertex, second_vertex);
  }
  parent[second_vertex] = first_vertex;
  if (rank[first_vertex] == rank[second_vertex]) {
    ++rank[second_vertex];
  }
}

void Graph::sort_vec_of_edges()
{
  std::sort(vec_of_edges.begin(), vec_of_edges.end(), comparator);
}

void KruskalMstFinder::kruskalAlgo() {
  graph.sort_vec_of_edges();
  parent.resize(graph.get_num_of_v());
  for (int i = 0; i < graph.get_num_of_v(); ++i) {
    parent[i] = i;
  }
  int edges_in_mst_counter = 0;
  for (int i = 0; i < graph.get_vec_of_edges().size(); ++i) {
    int first_vertex_parent = get_parent_otimized(graph.get_vec_of_edges()[i].begin);
    int second_vertex_parent = get_parent_otimized(graph.get_vec_of_edges()[i].end);
    if (first_vertex_parent != second_vertex_parent) {
      ++edges_in_mst_counter;
      unite_sets(first_vertex_parent, second_vertex_parent);
      mst_length += graph.get_vec_of_edges()[i].weight;
    }
    if (edges_in_mst_counter == graph.get_num_of_v() - 1) {
      break;
    }
  }
}

void input(int& num_of_v, std::vector<Edge>& vec_of_edges) {
  std::ifstream fin("kruskal.in");
  int num_of_e;
  fin >> num_of_v;
  fin >> num_of_e;
  vec_of_edges.resize(num_of_e);
  int begin;
  int end;
  int weight;
  for (int i = 0; i < num_of_e; ++i) {
    fin >> begin;
    fin >> end;
    fin >> weight;
    vec_of_edges[i] = Edge(begin - 1, end - 1, weight);
  }
  fin.close();
}

void output(int ans) {
  std::ofstream fout("kruskal.out");
  fout << ans;
  fout.close();
}

void solve() {
  int num_of_v;
  std::vector<Edge> vec_of_edges;
  input(num_of_v, vec_of_edges);
  Graph graph(num_of_v, vec_of_edges);
  KruskalMstFinder mst_finder(graph);
  mst_finder.kruskalAlgo();
  output(mst_finder.return_mst_length());
}
