#include <iostream>
#include <thread>
#include <memory>
#include <utility>
#include "classes.hpp"

using namespace std;

int main() {
  shared_ptr<Gate> gate = make_shared<Gate>();
  string name = "Alice";
  string address = "Alaska";
  thread th1(thread_func, gate, name, address);
  name = "Bob";
  address = "Brazil";
  thread th2(thread_func, gate, "Bob", "Brazil");
  name = "Chris";
  address = "Canada";
  thread th3(thread_func, gate, string("Chris"), string("Canada"));
  th1.join();
  th2.join();
  th3.join();
  return 0;
}


