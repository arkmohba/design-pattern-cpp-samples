#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <thread>

class Request {
 private:
  std::string __name;
  int __number;

 public:
  Request(std::string name, int number) : __name(name), __number(number) {}
  void execute();
  std::string to_string();
};

class Channel : public std::enable_shared_from_this<Channel> {
 private:
  static const int MAX_REQUEST = 100;
  std::unique_ptr<std::unique_ptr<Request>[]> request_queue;
  int tail, head, count;
  std::vector<std::unique_ptr<std::thread>> thread_pool;
  int __n_worker;
  std::mutex req_mutex;
  std::condition_variable req_cv;

 public:
  explicit Channel(int n_worker);
  void start_workers();
  void put_request(std::unique_ptr<Request> request);
  std::unique_ptr<Request> take_request();
};

void thread_func_worker(std::string name, std::weak_ptr<Channel> channel);
void thread_func_client(std::string name, std::weak_ptr<Channel> channel);
