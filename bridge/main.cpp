#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  string target1 = "Hello, japan.";
  string target2 = "Hello, World.";
  string target3 = "Hello, Universe.";
  DisplayImplPtr impl1 =
      unique_ptr<DisplayImpl>(new StringDisplayImpl(target1));
  DisplayPtr disp1 = make_unique<Display>(move(impl1));

  DisplayImplPtr impl2 =
      unique_ptr<DisplayImpl>(new StringDisplayImpl(target2));
  DisplayPtr disp2 = make_unique<Display>(move(impl2));

  DisplayImplPtr impl3 =
      unique_ptr<DisplayImpl>(new StringDisplayImpl(target3));
  unique_ptr<CountDisplay> disp3 = make_unique<CountDisplay>(move(impl3));

  disp1->display();
  disp2->display();
  disp3->display();
  disp3->multi_display(5);

  return 0;
}
