#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  DisplayPtr b1 = make_shared<StringDisplay>("Hello World.");
  DisplayPtr b2 = make_shared<SideBorder>(b1, '#');
  DisplayPtr b3 = make_shared<FullBorder>(b2);

  b1->show();
  b2->show();
  b3->show();
  DisplayPtr b4 = make_shared<SideBorder>(
      make_shared<FullBorder>(
          make_shared<FullBorder>(make_shared<SideBorder>(
              make_shared<FullBorder>(
                  make_shared<StringDisplay>("Hello!!!")),
              '*'))),
      '/');
  b4->show();
  return 0;
}
