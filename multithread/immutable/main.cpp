#include <thread>
#include <memory>
#include <utility>
#include "classes.hpp"

using namespace std;

int main() {
  auto alice  = make_shared<Person>("Alice", "Alaska");
  thread th1(thread_func_show, alice);
  thread th2(thread_func_show, alice);
  thread th3(thread_func_show, alice);
  th1.join();
  th2.join();
  th3.join();
  return 0;
}


