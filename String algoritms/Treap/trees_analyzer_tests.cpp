#include "gtest/gtest.h"
#include "../Solver.h"

#include <sstream>

TEST(height_width_diff_counter_tests, check_ans_1)
{
  std::stringstream input_stream;
  input_stream << "10\n"
    "5 11\n"
    "18 8\n"
    "25 7\n"
    "50 12\n"
    "30 30\n"
    "15 15\n"
    "20 10\n"
    "22 5\n"
    "40 20\n"
    "45 9\n";
  std::string correct_output;
  correct_output = "2\n1";
  std::stringstream my_output_stream;
  Solver height_width_diff_counter;
  height_width_diff_counter.input(input_stream);
  height_width_diff_counter.run();
  height_width_diff_counter.output_height_difference(my_output_stream);
  height_width_diff_counter.output_width_difference(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(height_width_diff_counter_tests, check_ans_2)
{
  std::stringstream input_stream;
  input_stream << "10\n"
    "38 19\n"
    "37 5\n"
    "47 15\n"
    "35 0\n"
    "12 3\n"
    "0 42\n"
    "31 37\n"
    "21 45\n"
    "30 26\n";
  std::string correct_output;
  correct_output = "2\n1";
  std::stringstream my_output_stream;
  Solver height_width_diff_counter;
  height_width_diff_counter.input(input_stream);
  height_width_diff_counter.run();
  height_width_diff_counter.output_height_difference(my_output_stream);
  height_width_diff_counter.output_width_difference(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

int main(int argc, char **argv) {
  printf("Running main() from trees_analyzer_tests.cpp\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
