#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

struct Node {
  vector<int>::const_iterator current;
  vector<int>::const_iterator end;

  bool operator>(const Node& other) const {
    return *current > *other.current;
  }
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  vector<int> res;
  std::priority_queue<Node, vector<Node>, std::greater<Node>> min_heap;

  for (const vector<int>& sorted_array : sorted_arrays) {
    if (!sorted_array.empty()) {
      min_heap.emplace(Node{sorted_array.cbegin(), sorted_array.cend()});
    }
  }

  while (!min_heap.empty()) {
    Node min = min_heap.top();
    min_heap.pop();
    res.push_back(*min.current);
    if (++min.current != min.end) {
      min_heap.emplace(Node{min.current, min.end});
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
