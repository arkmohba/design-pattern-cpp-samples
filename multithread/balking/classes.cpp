#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>

using namespace std;

void Data::do_save(string user) {
  cout << user << " calls do_save, content " << __content << endl;
  ofstream ofs(__filename);
  ofs << __content << endl;
  ofs.close();
}

void Data::change(std::string new_content) {
  lock_guard<mutex> lock(__mutex);
  __content = new_content;
  __changed = true;
}

void Data::save(string user) {
  lock_guard<mutex> lock(__mutex);
  if (!__changed) {
    // Balk
    return;
  }

  do_save(user);
  __changed = false;
}

void thread_func_saver(weak_ptr<Data> data_weak, std::string name) {
  for (int i = 0; i < 1000; i++) {
    auto data = data_weak.lock();
    if (!data) {
      break;
    }

    data->save(name);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void thread_func_changer(weak_ptr<Data> data_weak, std::string name) {
  auto rd = random_device{};
  std::mt19937 mt{rd()};
  std::uniform_int_distribution<int> dist(1, 1000);

  for (int i = 0; i < 1000; i++) {
    auto data = data_weak.lock();
    if (!data) {
      break;
    }

    string new_content = "No." + to_string(i);
    data->change(new_content);

    auto sleep_time = dist(mt);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

    data->save(name);
  }
}
