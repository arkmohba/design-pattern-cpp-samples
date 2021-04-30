#include <thread>
#include <memory>
#include <utility>
#include "classes.hpp"

using namespace std;

int main() {
  auto data_queue  = make_shared<RequestQueue>();
  thread th1(thread_func_get, data_queue, "Alice");
  thread th2(thread_func_put, data_queue, "Bobby");
  th1.join();
  th2.join();
  return 0;
}


