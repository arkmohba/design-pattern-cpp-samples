
#include "classes.hpp"

#include <iostream>

using namespace std;

Product* Factory::create(string owner) {
  Product* p = create_product(owner);
  register_product(p);
  return p;
}

IDCard::IDCard(string owner_) : owner(owner_) {
  cout << owner << "のカードを作ります" << endl;
}

void IDCard::use() { cout << owner << "のカードを使います" << endl; }

Product* IDCardFactory::create_product(string owner) {
  return new IDCard(owner);
}

void IDCardFactory::register_product(Product* product) {
  owners.push_back(
    static_cast<IDCard*>(product)->get_owner());
}
