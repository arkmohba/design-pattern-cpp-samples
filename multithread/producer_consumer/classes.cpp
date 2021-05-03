#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>

using namespace std;

void Table::put(string name, std::string cake) {
  lock_guard<mutex> lock(__put_mutex);

  cout << name << " puts " << cake << endl;
  {
    unique_lock<mutex> buf_lock(__mutex);
    __cv.wait(buf_lock, [this] { return count < n_dish; });
    buffer[tail] = cake;
    tail = (tail + 1) % n_dish;
    count++;
    __cv.notify_all();
  }
}

string Table::take(string name) {
  lock_guard<mutex> lock(__take_mutex);

  string cake;
  {
    unique_lock<mutex> buf_lock(__mutex);
    __cv.wait(buf_lock, [this] { return count > 0; });
    cake = buffer[head];
    head = (head + 1) % n_dish;
    count--;
    cout << name << " takes " << cake << endl;
    __cv.notify_all();
  }
  return cake;
}

int Counter::next_id() {
  lock_guard<mutex> lock(__mutex);
  auto now_id = count;
  count++;
  return now_id;
}

void thread_func_maker(weak_ptr<Table> table_weak, string name,
                       weak_ptr<Counter> cake_id_weak) {
  for (int i = 0; i < 1000; i++) {
    auto table = table_weak.lock();
    auto cake_id = cake_id_weak.lock();
    if (!table || !cake_id) {
      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    string cake =
        "[ Cake No." + to_string(cake_id->next_id()) + " by " + name + " ]";
    table->put(name, cake);
  }
}

void thread_func_eater(weak_ptr<Table> table_weak, std::string name) {
  auto rd = random_device{};
  std::mt19937 mt{rd()};
  std::uniform_int_distribution<int> dist(1, 1000);

  for (int i = 0; i < 1000; i++) {
    auto table = table_weak.lock();
    if (!table) {
      break;
    }

    string cake = table->take(name);

    auto sleep_time = dist(mt);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}
