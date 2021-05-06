#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <sstream>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>

using namespace std;

shared_ptr<TSLog> Log::get_ts_log() {
  static thread_local shared_ptr<TSLog> logger;
  if (!logger) {
    string name;
    if (__name.empty()) {
        stringstream name_ss;
        name_ss << this_thread::get_id() << "-log.txt";
        name = name_ss.str();
    } else {
        name = __name + "-log.txt";
    }
    logger = make_shared<TSLog>(name);
  }
  return logger;
}

thread_local string Log::__name = string();

void thread_func_client(string name) {
    cout << name << " BEGIN" << endl;
    Log::set_name(name);

    for (int i = 0; i < 10; i++) {
        Log::print_ln("i = " + to_string(i));
        this_thread::sleep_for(chrono::microseconds(100));
    }
    Log::close();
    cout << name << " END" << endl;
}