#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  cout << "main: BEGIN" << endl;

  auto count_up = make_shared<CountUp>();
  thread th(thread_func_count_up, count_up);

  this_thread::sleep_for(chrono::milliseconds(10000));

  cout << "main: shutdown_request" << endl;
  count_up->shutdown_request();

  cout << "main: join" << endl;
  th.join();

  cout << "main: END" << endl;
  return 0;
}
