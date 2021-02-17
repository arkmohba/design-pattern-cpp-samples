#include "classes.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string Gate::to_string() {
  static std::mutex mutex_str;
  std::lock_guard<std::mutex> lock(mutex_str);
  stringstream ss;
  ss << "No." << counter << ": " << name << ", " << address;
  return ss.str();
}

void Gate::check() {
  if (name[0] != address[0]) {
    cout << "***** BROKEN ***** " << to_string() << endl;
  }
}

void Gate::pass(string name_, string address_) {
  static std::mutex mutex_pass;
  std::lock_guard<std::mutex> lock(mutex_pass);
  counter++;
  name = name_;
  address = address_;
  check();
}

void thread_func(shared_ptr<Gate> gate, string name, string address) {
  cout << name << " BEGIN" << endl;
  int count = 0;
  while (true) {
    gate->pass(name, address);
    // usleep(int(1e5));
    if (count == 10000000) {
      printf("%d\n", gate->get_counter());
      count = 0;
    }
    count++;
  }
}
