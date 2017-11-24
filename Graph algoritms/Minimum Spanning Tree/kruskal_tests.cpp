#include "gtest/gtest.h"
#include "../kruskal.h"

TEST(kruskal_test, check_algo_res_1)
{
  int input_num_of_v = 4;
  int input_num_of_e = 4;
  std::vector<Edge> input_vec_of_edges = {
  { 1, 2, 1 },
  { 2, 3, 2 },
  { 3, 4, 5 },
  { 4, 1, 4 } };
  int correct_output = 7;

  std::vector<Edge> vec_of_edges;
  vec_of_edges.resize(input_num_of_e);
  int begin;
  int end;
  int weight;
  for (int i = 0; i < input_num_of_e; ++i) {
    begin = input_vec_of_edges[i].begin;
    end = input_vec_of_edges[i].end;
    weight = input_vec_of_edges[i].weight;
    vec_of_edges[i] = Edge(begin - 1, end - 1, weight);
  }

  Graph graph(input_num_of_v, vec_of_edges);
  KruskalMstFinder mst_finder(graph);
  mst_finder.kruskalAlgo();
  EXPECT_EQ(correct_output, mst_finder.return_mst_length());
}

TEST(kruskal_test, check_algo_res_2)
{
  int input_num_of_v = 4;
  int input_num_of_e = 4;
  std::vector<Edge> input_vec_of_edges = {
    { 1, 2, 1 },
    { 2, 3, 2 },
    { 2, 4, 3 },
    { 1, 4, 0 } };
  int correct_output = 3;

  std::vector<Edge> vec_of_edges;
  vec_of_edges.resize(input_num_of_e);
  int begin;
  int end;
  int weight;
  for (int i = 0; i < input_num_of_e; ++i) {
    begin = input_vec_of_edges[i].begin;
    end = input_vec_of_edges[i].end;
    weight = input_vec_of_edges[i].weight;
    vec_of_edges[i] = Edge(begin - 1, end - 1, weight);
  }

  Graph graph(input_num_of_v, vec_of_edges);
  KruskalMstFinder mst_finder(graph);
  mst_finder.kruskalAlgo();
  EXPECT_EQ(correct_output, mst_finder.return_mst_length());
}

TEST(kruskal_test, check_algo_res_3)
{
  int input_num_of_v = 2;
  int input_num_of_e = 1;
  std::vector<Edge> input_vec_of_edges = { { 1, 2, 100 } };
  int correct_output = 100;

  std::vector<Edge> vec_of_edges;
  vec_of_edges.resize(input_num_of_e);
  int begin;
  int end;
  int weight;
  for (int i = 0; i < input_num_of_e; ++i) {
    begin = input_vec_of_edges[i].begin;
    end = input_vec_of_edges[i].end;
    weight = input_vec_of_edges[i].weight;
    vec_of_edges[i] = Edge(begin - 1, end - 1, weight);
  }

  Graph graph(input_num_of_v, vec_of_edges);
  KruskalMstFinder mst_finder(graph);
  mst_finder.kruskalAlgo();
  EXPECT_EQ(correct_output, mst_finder.return_mst_length());
}

int main(int argc, char **argv) {
  printf("Running main() from kruskal_tests.cpp\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
