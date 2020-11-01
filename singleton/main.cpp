#include <iostream>
#include <string>

#include "classes.hpp"

using namespace std;

int main() {
  cout << "Start" << endl;
  Singleton* obj1 = Singleton::get_instance();
  Singleton* obj2 = Singleton::get_instance();
  if (obj1 == obj2) {
    cout << "obj1とobj2は同じインスタンスです。" << endl;
  } else {
    cout << "obj1とobj2は同じインスタンスではありません。" << endl;
  }
  cout << "End." << endl;
  return 0;
}
