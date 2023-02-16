#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct Node {
  bool isBalanced;
  int height;
};

Node CheckIsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree == nullptr) {
    return {true, -1};
  }

  auto left_result = CheckIsBalanced(tree->left);
  if (!left_result.isBalanced) {
    return {false, 0};
  }

  auto right_result = CheckIsBalanced(tree->right);
  if (!right_result.isBalanced) {
    return {false, 0};
  }

  bool is_balanced = abs(left_result.height - right_result.height) <= 1;
  int height = std::max(left_result.height, right_result.height) + 1;
  return {is_balanced, height};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return CheckIsBalanced(tree).isBalanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
