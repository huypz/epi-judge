#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool HasTwoSum(vector<int> A, int t) {
  int i = 0;
  int j = A.size() - 1;
  while (i <= j) {
    if (A[i] + A[j] == t) return true;
    else if (A[i] + A[j] < t) i++;
    else j--;
  }
  return false;
}

bool HasThreeSum(vector<int> A, int t) {
  sort(A.begin(), A.end());

  for (int a : A) {
    if (HasTwoSum(A, t - a)) return true;
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
