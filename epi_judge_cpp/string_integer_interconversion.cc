#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  string res;
  bool is_negative = x < 0;

  do {
    res += '0' + abs(x % 10);
    x /= 10;
  } while (x);

  if (is_negative) {
    res += '-';
  }

  return {res.rbegin(), res.rend()};
}
int StringToInt(const string& s) {
  int res = 0;
  int i = (s[0] == '+' || s[0] == '-') ? 1 : 0;
  for (; i < s.size(); i++) {
    int digit = s[i] - '0';
    res = res*10 + digit;
  }
  return s[0] == '-' ? -res : res;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
