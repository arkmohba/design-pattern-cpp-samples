#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  auto active_object = ActiveObjectFactory::create_active_object();
  thread th1(thread_func_maker, "Alice", active_object);
  thread th2(thread_func_maker, "Bobby", active_object);
  thread th3(thread_func_display, "Chris", active_object);
  th1.detach();
  th2.detach();
  th3.detach();

  this_thread::sleep_for(chrono::milliseconds(10000));
}
