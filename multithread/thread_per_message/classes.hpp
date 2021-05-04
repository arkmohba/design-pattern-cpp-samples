#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>

class Helper {
  void slowly();
 public:
  void handle(int count, char c);
};

class Host {
 private:
  Helper helper;

 public:
  void request(int n_print, char print_char);
};

