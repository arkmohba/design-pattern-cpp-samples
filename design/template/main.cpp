#include <iostream>
#include <string>

#include "classes.hpp"

using namespace std;
;
int main() {
  AbstractDisplay* d1 = new CharDisplay('H');
  AbstractDisplay* d2 = new StringDisplay("Hello, world.");
  // AbstractDisplay* d3 = new StringDisplay("こんにちは。");

  d1->display();
  d2->display();
  // d3->display();

  delete d1, d2;
  return 0;
}
