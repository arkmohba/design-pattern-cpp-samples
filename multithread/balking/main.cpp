#include <thread>
#include <memory>
#include <utility>
#include "classes.hpp"

using namespace std;

int main() {
  auto data  = make_shared<Data>("data.txt", "(empty)");
  thread th1(thread_func_saver, data, "SaverThread");
  thread th2(thread_func_changer, data, "ChangerThread");
  th1.join();
  th2.join();
  return 0;
}


