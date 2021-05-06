#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>

using namespace std;

std::shared_ptr<Data> Host::request(int count, char c) {
  cout << "        request(" << count << ", " << c << ") BEGIN" << endl;

  // FutureData
  auto future = make_shared<FutureData>();

  thread th([=] {
    auto real_data = make_unique<RealData>(count, c);
    future->set_real_data(move(real_data));
  });
  th.detach();
  cout << "        request(" << count << ", " << c << ") END" << endl;
  return future;
}

void FutureData::set_real_data(unique_ptr<RealData> real_data) {
  lock_guard<mutex> lock(__mutex);

  if (__ready) {
    return;
  }
  __real_data = move(real_data);
  __ready = true;
  __cv.notify_all();
}

string FutureData::get_content() {
  unique_lock<mutex> lock(__mutex);
  __cv.wait(lock, [this] {
    return __ready;
  });
  return __real_data->get_content();
}

RealData::RealData(int count, char c) : __count(count), __c(c) {
  __content = string(count, '*');
  for (int i = 0; i < count; i++) {
    __content[i] = c;
    this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  cout << "        making RealData(" << count << ", " << c << ") END" << endl;
}
