#include "gtest/gtest.h"
#include "../floyd.h"

#include <sstream>

TEST(floyd_test, check_ans_1)
{
  std::stringstream test_input_1;
  test_input_1 << "4\n"
    "0 5 9 100\n"
    "100 0 2 8\n"
    "100 100 0 7\n"
    "4 100 100 0";
  std::string test_correct_output_1;
  test_correct_output_1 =
    "0 5 7 13\n"
    "12 0 2 8\n"
    "11 16 0 7\n"
    "4 9 11 0\n";
  std::stringstream test_my_output_1;
  Solver solver;
  solver.input(test_input_1);
  solver.run();
  solver.output(test_my_output_1);
  //EXPECT_EQ(1, 0);
  EXPECT_EQ(test_correct_output_1, test_my_output_1.str());
}

TEST(floyd_test, check_ans_2)
{
  std::stringstream test_input_2;
  test_input_2 << "3\n"
    "0 100 3\n"
    "1 0 100\n"
    "5 100 0\n";
  std::string test_correct_output_2;
  test_correct_output_2 =
    "0 100 3\n"
    "1 0 4\n"
    "5 100 0\n";
  std::stringstream test_my_output_2;
  Solver solver;
  solver.input(test_input_2);
  solver.run();
  solver.output(test_my_output_2);
  //EXPECT_EQ(1,1);
  EXPECT_EQ(test_correct_output_2, test_my_output_2.str());
}

int main(int argc, char **argv) {
  printf("Running main() from floyd_tests.cpp\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
