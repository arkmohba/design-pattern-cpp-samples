#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

using namespace std;

std::unique_ptr<Request> RequestQueue::get_request() {
  // getter atomicity
  lock_guard<mutex> __lock(get_mutex);

  // wait for queue
  {
    // firstly lock
    unique_lock<mutex> queue_lock(queue_mutex);
    // unlock and waiting for put_request if empty else get data.
    queue_cv.wait(queue_lock, [this] { return !queue.empty(); });
  }
  auto req = move(queue.front());
  queue.pop_front();
  return move(req);
}

void RequestQueue::put_request(unique_ptr<Request> req) {
  // putter atomicity
  lock_guard<mutex> __lock(put_mutex);

  {
    unique_lock<mutex> queue_lock(queue_mutex);
    queue.push_back(move(req));
  }
  queue_cv.notify_one();
}

void thread_func_get(shared_ptr<RequestQueue> queue, std::string name) {
  for (int i = 0; i < 1000; i++) {
    auto request = queue->get_request();
    cout << name << " handles   " << request->get_name() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void thread_func_put(shared_ptr<RequestQueue> queue, std::string name) {
  for (int i = 0; i < 1000; i++) {
    string req_name = "No." + to_string(i);
    auto request = make_unique<Request>(req_name);
    cout << name << " requests " << request->to_string() << endl;
    queue->put_request(move(request));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
