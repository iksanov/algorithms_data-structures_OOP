#include "gtest/gtest.h"
#include "../Solver.h"

#include <sstream>

TEST(second_statistics, check_ans_1)
{
  std::stringstream input_stream;
  input_stream <<
    "10 3\n"
    "1 2 3 4 5 6 7 8 9 10\n"
    "1 2\n"
    "1 10\n"
    "2 7\n";
  std::string correct_output;
  correct_output = "2\n2\n3\n";
  std::stringstream my_output_stream;
  Solver second_statistics_finder;
  second_statistics_finder.input(input_stream);
  second_statistics_finder.run();
  second_statistics_finder.output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(second_statistics, check_ans_2)
{
  std::stringstream input_stream;
  input_stream <<
    "8 3\n"
    "0 -1 -1 61 4 -1 -9 -32\n"
    "1 2\n"
    "2 5\n"
    "1 8\n";
  std::string correct_output;
  correct_output = "0\n-1\n-9\n";
  std::stringstream my_output_stream;
  Solver second_statistics_finder;
  second_statistics_finder.input(input_stream);
  second_statistics_finder.run();
  second_statistics_finder.output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

int main(int argc, char **argv) {
  printf("Running main() from second_statistics_tests.cpp\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
