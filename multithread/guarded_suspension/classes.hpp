#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <string>

class Request {
 private:
  std::string __name;

 public:
  explicit Request(std::string name) : __name(name) {}
  std::string get_name() { return __name; }
  std::string to_string() { return "[ Request " + __name + " ]"; }
};

class RequestQueue {
 private:
  std::mutex get_mutex;
  std::mutex put_mutex;
  std::deque<std::unique_ptr<Request>> queue;
  std::mutex queue_mutex;
  std::condition_variable queue_cv;

 public:
  std::unique_ptr<Request> get_request();
  void put_request(std::unique_ptr<Request> request);
};

void thread_func_put(std::shared_ptr<RequestQueue> queue, std::string name);
void thread_func_get(std::shared_ptr<RequestQueue> queue, std::string name);
