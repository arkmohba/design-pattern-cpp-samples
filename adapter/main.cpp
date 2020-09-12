#include <iostream>
#include <string>
#include "classes.hpp"

using namespace std;

int main() {
  Print* p = new PrintBanner("Hello");
  p->printWeak();
  p->printStrong();
  delete p;

  Print* p2 = new PrintBannerTransfer("ByeBye");
  p2->printWeak();
  p2->printStrong();
  delete p2;
  return 0;
}


