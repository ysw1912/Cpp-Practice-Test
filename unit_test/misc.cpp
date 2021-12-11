
#include <iostream>
#include <string>
#include <set>

#include <cstring>

#include "output.h"

using namespace std;

struct Cmp {
  bool operator()(const string& x, const string& y) const {
    printf("op = %d\n", strncasecmp(x.c_str(), y.c_str(), x.size() > y.size() ? y.size() : x.size()));
    return strncasecmp(x.c_str(), y.c_str(), x.size() > y.size() ? y.size() : x.size()) > 0;
  }
};

int main(int argc, char const *argv[]) {
  set<string, Cmp> s;
  s.emplace("comm2");
  cout << s << endl;
  cout << *s.find("comm2/") << endl;
  return 0;
}
