#include "Solver.h"
#include "PrefixFunctionCounter.h"

void Solver::input(std::istream& in) {
  in >> pattern;
  in >> text;
}

void Solver::run_with_output(std::ostream& out) {
  std::string pattern_with_separator = pattern + '#';
  prefix_function_values.resize(pattern_with_separator.length());
  PrefixFunctionCounter::count_prefix_function(pattern_with_separator, prefix_function_values);
  //organise evaluating prefix_function "on-line" not to waste (n + m) memory but only m
  //We just evaluate prefix_function_values one-by-one and output just at once if necessary
  int cur_prefix_func_value = prefix_function_values[prefix_function_values.size() - 1];
  for (int i = 0; i < text.length(); ++i) {
    int possible_suff_len = cur_prefix_func_value;
    while (possible_suff_len > 0 && text[i] != pattern[possible_suff_len]) {
      possible_suff_len = prefix_function_values[possible_suff_len - 1];
    }
    if (text[i] == pattern[possible_suff_len]) {
      cur_prefix_func_value = possible_suff_len + 1;
    }
    else {
      cur_prefix_func_value = 0;
    }
    if (cur_prefix_func_value == pattern.length()) { //output
      out << i - pattern.size() + 1 << " ";
    }
  }
}
