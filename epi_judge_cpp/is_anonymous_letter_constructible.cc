#include <string>

#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  std::unordered_map<char, int> map;
  for (const char& c : letter_text) {
    ++map[c];
  }
  for (const char& c : magazine_text) {
    auto it = map.find(c);
    if (it != map.cend()) {
      --it->second;
      if (it->second == 0) {
        map.erase(it);
        if (map.empty()) 
          break;
      }
    }
  }

  return map.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
