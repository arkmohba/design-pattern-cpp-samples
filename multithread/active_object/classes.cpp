#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>

using namespace std;

shared_ptr<Result<std::string>> Proxy::make_string(int count, char fill_char) {
  // 戻り値として最終的に使うFutureオブジェクトを作る。
  auto future = make_shared<FutureResult<string>>();
  // メソッドの起動だけ行う
  __scheduler->invoke(
      make_shared<MakeStringRequest>(__servant, future, count, fill_char));
  return future;
}

void Proxy::display_string(string s) {
  // Note: 戻り値がないのでFutureパターンはしなくて良い。
  __scheduler->invoke(make_shared<DisplayStringRequest>(__servant, s));
}

shared_ptr<Result<std::string>> Servant::make_string(int count,
                                                     char fill_char) {
  string buffer = string(count, '*');
  for (int i = 0; i < count; i++) {
    buffer[i] = fill_char;
    this_thread::sleep_for(chrono::milliseconds(100));
  }
  return make_shared<RealResult<string>>(buffer);
}

void Servant::display_string(string s) {
  this_thread::sleep_for(chrono::milliseconds(10));
}

template <class T>
void ActivationQueue<T>::put_request(
    std::shared_ptr<MethodRequest<T>> request) {
  lock_guard<mutex> lock(__put_mutex);

  {
    unique_lock<mutex> buf_lock(__mutex);
    __cv.wait(buf_lock, [this] { return count < MAX_METHOD_REQUEST; });
    request_queue[tail] = request;
    tail = (tail + 1) % MAX_METHOD_REQUEST;
    count++;
    __cv.notify_all();
  }
}

template <class T>
std::shared_ptr<MethodRequest<T>> ActivationQueue<T>::take_request() {
  lock_guard<mutex> lock(__take_mutex);

  std::shared_ptr<MethodRequest<T>> request;
  {
    unique_lock<mutex> buf_lock(__mutex);
    __cv.wait(buf_lock, [this] { return count > 0; });
    request = request_queue[head];
    head = (head + 1) % MAX_METHOD_REQUEST;
    count--;
    __cv.notify_all();
  }
  return request;
}

template <class T>
void SchedulerThread<T>::start() {
  th = thread([this] {
    while (true) {
      auto request = __queue->take_request();
      request->execute();
    }
  });
  th.detach();
}

void MakeStringRequest::execute() {
  auto result = __servant->make_string(__count, __fill_char);
  __future->set_result(result);
}

void DisplayStringRequest::execute() {
  cout << __str << endl;
  if (!__servant) {
    cout << "__servant cannot be used" << endl;
  }
  __servant->display_string(__str);
}

template <class T>
void FutureResult<T>::set_result(shared_ptr<Result<T>> result) {
  lock_guard<mutex> lock(__mutex);

  if (__ready) {
    return;
  }
  __result = result;
  __ready = true;
  __cv.notify_all();
}

template <class T>
T FutureResult<T>::get_result_value() {
  unique_lock<mutex> lock(__mutex);
  __cv.wait(lock, [this] { return __ready; });
  return __result->get_result_value();
}

shared_ptr<ActiveObject> ActiveObjectFactory::create_active_object() {
  auto servant = make_shared<Servant>();
  auto queue = make_shared<ActivationQueue<string>>();
  auto scheduler = make_shared<SchedulerThread<string>>(queue);
  auto proxy = make_shared<Proxy>(scheduler, servant);

  scheduler->start();

  return proxy;
}

void thread_func_maker(string name, shared_ptr<ActiveObject> active_object) {
  char fill_char = name[0];
  for (int i = 0; true; i++) {
    auto result = active_object->make_string(i, fill_char);
    this_thread::sleep_for(chrono::milliseconds(10));
    string value = result->get_result_value();
    cout << name << ": value = " << value << endl;
  }
}

void thread_func_display(string name, shared_ptr<ActiveObject> active_object) {
  for (int i = 0; true; i++) {
    string s = name + " " + to_string(i);
    active_object->display_string(s);
    this_thread::sleep_for(chrono::milliseconds(200));
  }
}
