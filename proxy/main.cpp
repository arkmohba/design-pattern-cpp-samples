#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"
using namespace std;

int main() {
  shared_ptr<Printable> p = make_shared<PrinterProxy>("Alice");
  cout << "名前は現在" << p->get_printer_name() << "です。" << endl;
  p->set_printer_name("Bob");
  cout << "名前は現在" << p->get_printer_name() << "です。" << endl;
  p->print("Hello world");
  return 0;
}
