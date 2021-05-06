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

static const char STRING_DEFAULT_CHAR = '*';

void ReadWriteLock::read_lock() {
  // readerの追加
  lock_guard<mutex> lock(rl_mutex);
  // writer待ち
  {
    unique_lock<mutex> data_lock(data_mutex);
    cv.wait(data_lock, [this] {
      return writing_writers == 0 && (!prefer_writer || waiting_writers == 0);
    });
    reading_readears++;
  }
}

void ReadWriteLock::read_unlock() {
  lock_guard<mutex> lock(rul_mutex);

  {
    lock_guard<mutex> lock(data_mutex);
    reading_readears--;
    prefer_writer = true;
    cv.notify_all();
  }
}

void ReadWriteLock::write_lock() {
  lock_guard<mutex> lock(wl_mutex);
  {
    unique_lock<mutex> data_lock(data_mutex);
    waiting_writers++;
    cv.wait(data_lock,
            [this] { return reading_readears == 0 && writing_writers == 0; });
    waiting_writers--;
    writing_writers++;
  }
}

void ReadWriteLock::write_unlock() {
  lock_guard<mutex> lock(wul_mutex);
  {
    lock_guard<mutex> lock(data_mutex);
    writing_writers--;
    prefer_writer = false;
    cv.notify_all();
  }
}

Data::Data(int size) { __buffer = string(size, STRING_DEFAULT_CHAR); }

string Data::do_read() {
  // 下記のコピーは原文ママ
  string new_buf = string(__buffer.size(), STRING_DEFAULT_CHAR);
  for (int i = 0; i < __buffer.size(); i++) {
    new_buf[i] = __buffer[i];
  }
  slowly();
  return new_buf;
}

void Data::do_write(char c) {
  for (int i = 0; i < __buffer.size(); i++) {
    __buffer[i] = c;
    slowly();
  }
}

string Data::read() {
  __lock.read_lock();
  string res = do_read();
  __lock.read_unlock();
  return res;
}

void Data::write(char c) {
  __lock.write_lock();
  do_write(c);
  __lock.write_unlock();
}

void Data::slowly() {
  auto rd = random_device{};
  std::mt19937 mt{rd()};
  std::uniform_int_distribution<int> dist(1, 50);
  auto sleep_time = dist(mt);
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
}

void thread_func_writer(weak_ptr<Data> data_weak, string filler) {
  int index = 0;
  auto rd = random_device{};
  std::mt19937 mt{rd()};
  std::uniform_int_distribution<int> dist(1, 3000);

  for (int i = 0; i < 1000; i++) {
    auto data = data_weak.lock();
    if (!data) {
      break;
    }
    char c = filler[index];
    data->write(c);
    index = (index + 1) % filler.length();

    auto sleep_time = dist(mt);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

void thread_func_reader(weak_ptr<Data> data_weak, string name) {
  for (int i = 0; i < 1000; i++) {
    auto data = data_weak.lock();
    if (!data) {
      break;
    }

    auto read_buf = data->read();
    cout << name << " reads " << read_buf << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
