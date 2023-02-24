#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

struct Entry {
  const unique_ptr<BinaryTreeNode<int>>& node;
  int low;
  int high;
};

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  std::queue<Entry> bfs_queue;
  bfs_queue.emplace(Entry{tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()});

  while (!bfs_queue.empty()) {
    if (bfs_queue.front().node.get()) {
      if (bfs_queue.front().node->data < bfs_queue.front().low || bfs_queue.front().node->data > bfs_queue.front().high) {
        return false;
      }
      bfs_queue.emplace(Entry{bfs_queue.front().node->left, bfs_queue.front().low, bfs_queue.front().node->data});
      bfs_queue.emplace(Entry{bfs_queue.front().node->right, bfs_queue.front().node->data, bfs_queue.front().high});
    }
    bfs_queue.pop();
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
