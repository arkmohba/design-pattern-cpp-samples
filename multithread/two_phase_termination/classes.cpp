#include "classes.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

using namespace std;

void CountUp::shutdown_request() { shutdown_requested = true; }

void CountUp::do_work() {
  counter++;
  cout << "do_work: counter = " << counter << endl;
  this_thread::sleep_for(chrono::milliseconds(500));
}

void CountUp::do_shutdown() {
  cout << "do_shutdown: counter = " << counter << endl;
}

void thread_func_count_up(weak_ptr<CountUp> count_up_weak) {
  auto count_up = count_up_weak.lock();
  for (int i = 0; i < 1000; i++) {
    if (count_up->is_shutdown_requested()) break;
    count_up->do_work();
  }
  count_up->do_shutdown();
}
