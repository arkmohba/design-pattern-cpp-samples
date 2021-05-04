#include <thread>
#include <memory>
#include <utility>
#include "classes.hpp"

using namespace std;

int main() {
  auto data  = make_shared<Data>(10);
  thread th1(thread_func_reader, data, "Reader-1");
  thread th2(thread_func_reader, data, "Reader-2");
  thread th3(thread_func_reader, data, "Reader-3");
  thread th4(thread_func_reader, data, "Reader-4");
  thread th5(thread_func_reader, data, "Reader-5");
  thread th6(thread_func_reader, data, "Reader-6");
  thread th7(thread_func_writer, data, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  thread th8(thread_func_writer, data, "abcdefghijklmnopqrstuvwxyz");
  th1.join();
  th2.join();
  th3.join();
  th4.join();
  th5.join();
  th6.join();
  th7.join();
  th8.join();
  
  return 0;
}


