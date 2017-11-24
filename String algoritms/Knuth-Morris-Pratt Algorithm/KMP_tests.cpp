#include "gtest/gtest.h"
//#include "../State.h"
#include "../Solver.h"

#include <sstream>

TEST(KMP_test, check_ans_1)
{
  std::stringstream input_stream;
  input_stream <<
    "aba\n"
    "abacababa";
  std::string correct_output;
  correct_output = "0 4 6 ";
  std::stringstream my_output_stream;
  Solver KMPSustringsFinder;
  KMPSustringsFinder.input(input_stream);
  KMPSustringsFinder.run_with_output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(KMP_test, check_ans_2)
{
  std::stringstream input_stream;
  input_stream <<
    "a\n"
    "aaaaaa";
  std::string correct_output;
  correct_output = "0 1 2 3 4 5 ";
  std::stringstream my_output_stream;
  Solver KMPSustringsFinder;
  KMPSustringsFinder.input(input_stream);
  KMPSustringsFinder.run_with_output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(KMP_test, check_wrong_pattern)
{
  std::stringstream input_stream;
  input_stream <<
    "z\n"
    "abacababa";
  std::string correct_output;
  correct_output = "";
  std::stringstream my_output_stream;
  Solver KMPSustringsFinder;
  KMPSustringsFinder.input(input_stream);
  KMPSustringsFinder.run_with_output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

TEST(KMP_test, check_equality)
{
  std::stringstream input_stream;
  input_stream <<
    "abacab\n"
    "abacab";
  std::string correct_output;
  correct_output = "0 ";
  std::stringstream my_output_stream;
  Solver KMPSustringsFinder;
  KMPSustringsFinder.input(input_stream);
  KMPSustringsFinder.run_with_output(my_output_stream);
  EXPECT_EQ(correct_output, my_output_stream.str());
}

int main(int argc, char **argv) {
  printf("Running main() from KMP_tests.cpp\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
