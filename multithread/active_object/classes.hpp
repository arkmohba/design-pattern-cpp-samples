#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

template <class T>
class Result {
 public:
  virtual T get_result_value() = 0;
};

template <class T>
class FutureResult : public Result<T> {
 private:
  std::shared_ptr<Result<T>> __result;
  bool __ready;
  std::mutex __mutex;
  std::condition_variable __cv;

 public:
  FutureResult() : __ready(false) {}
  void set_result(std::shared_ptr<Result<T>> result);
  T get_result_value();
};

template <class T>
class RealResult : public Result<T> {
 private:
  T __result_value;

 public:
  explicit RealResult(T result_value) : __result_value(result_value) {}
  T get_result_value() { return __result_value; }
};

class Servant;
class Proxy;

template <class T>
class MethodRequest {
 protected:
  std::shared_ptr<Servant> __servant;
  std::shared_ptr<FutureResult<T>> __future;
  MethodRequest(std::shared_ptr<Servant> servant,
                std::shared_ptr<FutureResult<T>> future)
      : __servant(servant), __future(future) {}

 public:
  virtual void execute() = 0;
};

template <class T>
class ActivationQueue {
 private:
  static const int MAX_METHOD_REQUEST = 100;
  std::mutex __put_mutex, __take_mutex;
  std::mutex __mutex;
  std::condition_variable __cv;
  std::unique_ptr<std::shared_ptr<MethodRequest<T>>[]> request_queue;
  int tail, head, count;

 public:
  ActivationQueue() : tail(0), head(0), count(0) {
    request_queue = std::make_unique<std::shared_ptr<MethodRequest<T>>[]>(
        MAX_METHOD_REQUEST);
  }
  void put_request(std::shared_ptr<MethodRequest<T>> request);
  std::shared_ptr<MethodRequest<T>> take_request();
};

template <class T>
class SchedulerThread {
 private:
  std::shared_ptr<ActivationQueue<T>> __queue;
  std::thread th;

 public:
  explicit SchedulerThread(std::shared_ptr<ActivationQueue<T>> queue) {
    __queue = queue;
  }
  void invoke(std::shared_ptr<MethodRequest<T>> request) {  // メソッドの起動
    __queue->put_request(request);
  }
  void start();  // スレッドの起動
};

class ActiveObject {
 public:
  virtual std::shared_ptr<Result<std::string>> make_string(int i,
                                                           char fill_char) = 0;
  virtual void display_string(std::string s) = 0;
};

class Proxy : public ActiveObject {
 private:
  std::shared_ptr<SchedulerThread<std::string>> __scheduler;
  std::shared_ptr<Servant> __servant;

 public:
  Proxy(std::shared_ptr<SchedulerThread<std::string>> scheduler,
        std::shared_ptr<Servant> servant)
      : __scheduler(scheduler), __servant(servant) {}
  std::shared_ptr<Result<std::string>> make_string(int count, char fill_char);
  void display_string(std::string s);
};

class Servant : public ActiveObject {
 public:
  std::shared_ptr<Result<std::string>> make_string(int count, char fill_char);
  void display_string(std::string s);
};

class MakeStringRequest : public MethodRequest<std::string> {
 private:
  int __count;
  char __fill_char;

 public:
  MakeStringRequest(std::shared_ptr<Servant> servant,
                    std::shared_ptr<FutureResult<std::string>> future,
                    int count, char fill_char)
      : MethodRequest(servant, future),
        __count(count),
        __fill_char(fill_char) {}
  void execute();
};

class DisplayStringRequest : public MethodRequest<std::string> {
 private:
  std::string __str;

 public:
  DisplayStringRequest(std::shared_ptr<Servant> servant, std::string s)
      : MethodRequest(servant, nullptr), __str(s) {}
  void execute();
};

class ActiveObjectFactory {
 public:
  static std::shared_ptr<ActiveObject> create_active_object();
};

void thread_func_maker(std::string name,
                       std::shared_ptr<ActiveObject> active_object);
void thread_func_display(std::string name,
                         std::shared_ptr<ActiveObject> active_object);
