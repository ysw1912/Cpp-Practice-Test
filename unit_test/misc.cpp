
#include <iostream>
#include <vector>

using namespace std;

class Obj1 {
 public:
  Obj1()
  {
    cout << "Obj1()\n";
  }
  Obj1(const Obj1&)
  {
    cout << "Obj1(const Obj1&)\n";
  }
  Obj1(Obj1&&)
  {
    cout << "Obj1(Obj1&&)\n";
  }
};

class Obj2 {
 public:
  Obj2()
  {
    cout << "Obj2()\n";
  }
  Obj2(const Obj2&)
  {
    cout << "Obj2(const Obj2&)\n";
  }
  Obj2(Obj2&&) noexcept
  {
    cout << "Obj2(Obj2&&)\n";
  }
};

int main()
{
  vector<Obj1> v1;
  for (int i = 0; i < 5; i++) {
    v1.emplace_back();
  }

}
