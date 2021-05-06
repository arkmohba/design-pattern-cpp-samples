#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>

class Data {
 public:
  virtual std::string get_content() = 0;
};

class RealData : public Data {
  int __count;
  char __c;
  std::string __content;

 public:
  RealData(int count, char c);
  std::string get_content() {
    return __content;
  }
};

class FutureData : public Data {
 private:
  std::unique_ptr<RealData> __real_data;
  bool __ready;
  std::mutex __mutex;
  std::condition_variable __cv;

 public:
  FutureData() : __ready(false) {}
  void set_real_data(std::unique_ptr<RealData>);
  std::string get_content();
};

class Host {
 private:

 public:
  std::shared_ptr<Data> request(int n_print, char print_char);
  std::string get_content();
};
