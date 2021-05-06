#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  thread th1(thread_func_client, "Alice");
  thread th2(thread_func_client, "Bobby");
  thread th3(thread_func_client, "Chris");
  th1.join();
  th2.join();
  th3.join();
  return 0;
}
