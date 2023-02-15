#include <stdexcept>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::length_error;

class Stack {
 private:
  struct Element {
    int value, max;
  };
  int capacity;
  int size;
  int max;
  Element* arr;
  
 public:
  Stack() {
    capacity = 1;
    size = 0;
    max = INT_MIN;
    arr = new Element[capacity];
  }
  ~Stack() {
    delete [] arr;
  }
  bool Empty() const {
    return size == 0;
  }
  int Max() const {
    if (Empty()) {
      throw length_error("Max(): empty stack");
    }
    return arr[size-1].max;
  }
  int Pop() {
    if (Empty()) {
      throw length_error("Pop(): empty stack");
    }
    return arr[--size].value;
  }
  void Push(int x) {
    if (size == capacity) {
      capacity *= 2;
      Element* new_arr = new Element[capacity];
      for (int i = 0; i < size; i++) {
        new_arr[i] = arr[i];
      }
      delete [] arr;
      arr = new_arr;
    }

    Element e{x, std::max(x, Empty() ? x : Max())};
    arr[size++] = e;
    return;
  }
};
struct StackOp {
  std::string op;
  int argument;
};

namespace test_framework {
template <>
struct SerializationTrait<StackOp> : UserSerTrait<StackOp, std::string, int> {};
}  // namespace test_framework

void StackTester(const std::vector<StackOp>& ops) {
  try {
    Stack s;
    for (auto& x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
