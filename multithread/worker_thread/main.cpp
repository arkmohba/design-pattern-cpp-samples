#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  auto channel = make_shared<Channel>(5);
  channel->start_workers();
  thread th1(thread_func_client, "Alice", channel);
  thread th2(thread_func_client, "Bobby", channel);
  thread th3(thread_func_client, "Chris", channel);
  th1.detach();
  th2.detach();
  th3.detach();
  std::this_thread::sleep_for(std::chrono::milliseconds(100000));
  return 0;
}
