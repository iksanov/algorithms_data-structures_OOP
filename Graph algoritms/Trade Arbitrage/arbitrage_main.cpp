#include <iostream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

struct Edge {
  Edge(int from_, int to_, float weight_) : from(from_), to(to_), weight(weight_) {}
  int from;
  int to;
  float weight;
};

struct ExchangeGraph {
  size_t num_currencies;
  vector<Edge> edges;
};

void input(ExchangeGraph& graph) {
  cin >> graph.num_currencies;
  for (int i = 0; i < graph.num_currencies; ++i) {
    for (int j = 0; j < graph.num_currencies; ++j) {
      if (i != j) {
        float some;
        cin >> some;
        if (some != -1)
          graph.edges.push_back(Edge(i, j, some));
      }
    }
  }
}

void output(bool ans) {
  if (ans == true) {
    cout << "YES";
  }
  else {
    cout << "NO";
  }
}

bool check_negative_cycle(const ExchangeGraph& graph, vector<float>& nodes) {
  for (int k = 0; k < graph.num_currencies; ++k) { //for each vertex
    nodes.resize(graph.num_currencies, 0);
    nodes[k] = 1;
    for (int j = 0; j < graph.num_currencies - 1; ++j) { //N-1 times relax each edge
      for (int i = 0; i < graph.edges.size(); ++i) {
        if (nodes[graph.edges[i].to] < nodes[graph.edges[i].from] * graph.edges[i].weight) {
          nodes[graph.edges[i].to] = nodes[graph.edges[i].from] * graph.edges[i].weight;
        }
      }
    }
    for (int i = 0; i < graph.edges.size(); ++i) {
      //if we have managed to relaxed one more time, it means that there is a cycle of a negative weight
      if (nodes[graph.edges[i].to] < nodes[graph.edges[i].from] * graph.edges[i].weight) {
        return true;
      }
    }
    return false;
  }
}

int main() {
  int num_nodes;
  vector<Edge> edges;
  vector<float> nodes;
  ExchangeGraph  graph;
  input(graph);
  output(check_negative_cycle(graph, nodes));
  return 0;
}
