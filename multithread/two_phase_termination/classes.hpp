#include <memory>

class CountUp {
 private:
  unsigned int counter = 0;
  bool shutdown_requested = false;

 public:
  void shutdown_request();
  bool is_shutdown_requested() { return shutdown_requested; }
  void do_work();
  void do_shutdown();
};

void thread_func_count_up(std::weak_ptr<CountUp> count_up_weak);
