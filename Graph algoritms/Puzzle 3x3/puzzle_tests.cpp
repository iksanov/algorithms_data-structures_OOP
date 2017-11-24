#include "gtest/gtest.h"
#include "../State.h"
#include "../Solver.h"

#include <sstream>

TEST(puzzle_3x3_test, check_ans_1)
{
  std::stringstream input_stream;
  input_stream <<
    "0 1 6\n"
    "4 3 2\n"
    "7 5 8\n";
  std::string correct_output;
  correct_output = "8\n"
  "RDRULDDR\n";
  std::stringstream my_output_stream;
  Solver puzzle_solver;
  puzzle_solver.input(input_stream);
  puzzle_solver.run();
  puzzle_solver.output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(puzzle_3x3_test, check_ans_2)
{
  std::stringstream input_stream;
  input_stream <<
    "1 2 3\n"
    "4 5 0\n"
    "7 8 6\n";
  std::string correct_output;
  correct_output = "1\n"
    "D\n";
  std::stringstream my_output_stream;
  Solver puzzle_solver;
  puzzle_solver.input(input_stream);
  puzzle_solver.run();
  puzzle_solver.output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(puzzle_3x3_test, incorrect_1)
{
  std::stringstream input_stream;
  input_stream <<
    "1 2 3\n"
    "8 0 4\n"
    "7 6 5\n";
  std::string correct_output;
  correct_output = "-1\n";
  std::stringstream my_output_stream;
  Solver puzzle_solver;
  puzzle_solver.input(input_stream);
  puzzle_solver.run();
  puzzle_solver.output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(puzzle_3x3_test, incorrect_2)
{
  std::stringstream input_stream;
  input_stream <<
    "1 2 3\n"
    "4 5 6\n"
    "8 7 0\n";
  std::string correct_output;
  correct_output = "-1\n";
  std::stringstream my_output_stream;
  Solver puzzle_solver;
  puzzle_solver.input(input_stream);
  puzzle_solver.run();
  puzzle_solver.output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(puzzle_3x3_test, initial)
{
  std::stringstream input_stream;
  input_stream <<
    "1 2 3\n"
    "4 5 6\n"
    "7 8 0\n";
  std::string correct_output;
  correct_output = "0\n";
  std::stringstream my_output_stream;
  Solver puzzle_solver;
  puzzle_solver.input(input_stream);
  puzzle_solver.run();
  puzzle_solver.output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

int main(int argc, char **argv) {
  printf("Running main() from puzzle_tests.cpp\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
