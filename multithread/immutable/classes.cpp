#include "classes.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

std::string Person::to_string() {
  stringstream ss;
  ss << "[ Person: name = " << __name << ", address = " << __address << " ]";
  return ss.str();
}

void thread_func_show(std::shared_ptr<Person> person) {
  const std::thread::id tid = std::this_thread::get_id();
  while (true) {
    sleep(0.1);
    cout << "Thread-" << tid << " prints " << person->to_string() << endl;
  }
}
