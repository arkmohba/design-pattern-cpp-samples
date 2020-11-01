#include <iostream>
#include <string>

#include "classes.hpp"

using namespace std;
;
int main() {
  Factory* factory = new IDCardFactory();
  Product* card1 = factory->create("Aさん");
  Product* card2 = factory->create("Bさん");
  Product* card3 = factory->create("Cさん");
  card1->use();
  card2->use();
  card3->use();

  delete card1, card2, card3;
  return 0;
}
