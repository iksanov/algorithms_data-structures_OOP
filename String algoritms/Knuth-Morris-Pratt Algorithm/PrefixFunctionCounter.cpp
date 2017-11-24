#include "PrefixFunctionCounter.h"

void PrefixFunctionCounter::count_prefix_function(std::string& str, std::vector<int>& prefix_func) {
  prefix_func[0] = 0;
  for (int i = 1; i < str.size(); ++i) {
    //next possible length of suffix (or prefix) (less then current)
    //that will save prefix-suffix-equals-property
    int possible_suff_len = prefix_func[i - 1];
    while (possible_suff_len > 0 && str[i] != str[possible_suff_len]) {
      possible_suff_len = prefix_func[possible_suff_len - 1];
    }
    if (str[i] == str[possible_suff_len]) { //also consider the case when (possible_suff_len == 0) and (str[i] == str[0])
      prefix_func[i] = possible_suff_len + 1;
    }
    else {
      prefix_func[i] = 0; //the case when (possible_suff_len == 0) and (str[i] != str[0])
    }
  }
}
