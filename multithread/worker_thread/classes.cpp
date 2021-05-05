#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>

using namespace std;

void Request::execute() {
  static auto rd = random_device{};
  static mt19937 mt{rd()};
  static uniform_int_distribution<int> dist(1, 1000);

  cout << __name << " executes " << to_string() << endl;
  auto sleep_time = dist(mt);
  this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
}

string Request::to_string() {
  return "[ Request from " + __name + " No." + std::to_string(__number) + " ]";
}

Channel::Channel(int n_worker) : __n_worker(n_worker) {
  request_queue = make_unique<unique_ptr<Request>[]>(MAX_REQUEST);
  head = 0;
  tail = 0;
  count = 0;
}

void Channel::start_workers() {
  for (int i = 0; i < __n_worker; i++) {
    thread_pool.push_back(make_unique<thread>(
        thread_func_worker, "Worker-" + std::to_string(i), shared_from_this()));
    thread_pool.back()->detach();
  }
}

void Channel::put_request(unique_ptr<Request> request) {
  unique_lock<mutex> lock(req_mutex);
  req_cv.wait(lock, [this] { return count < MAX_REQUEST; });
  request_queue[tail] = move(request);
  tail = (tail + 1) % MAX_REQUEST;
  count++;
  req_cv.notify_all();
}

unique_ptr<Request> Channel::take_request() {
  unique_lock<mutex> lock(req_mutex);
  req_cv.wait(lock, [this] { return count > 0; });
  auto request = move(request_queue[head]);
  head = (head + 1) % MAX_REQUEST;
  count--;
  req_cv.notify_all();
  return move(request);
}

void thread_func_worker(string name, weak_ptr<Channel> channel_weak) {
  for (int i = 0; i < 100; i++) {
    auto channel = channel_weak.lock();
    if (!channel) {
      return;
    }
    auto request = channel->take_request();
    request->execute();
  }
}

void thread_func_client(string name, weak_ptr<Channel> channel_weak) {
  auto rd = random_device{};
  mt19937 mt{rd()};
  uniform_int_distribution<int> dist(1, 100);

  for (int i = 0; i < 50; i++) {
    auto channel = channel_weak.lock();
    if (!channel) {
      return;
    }
    auto request = make_unique<Request>(name, i);
    channel->put_request(move(request));

    cout << name << " put request" << endl;
    auto sleep_time = dist(mt);
    this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}