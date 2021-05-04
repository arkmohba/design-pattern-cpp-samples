#include <memory>
#include <mutex>
#include <condition_variable>
#include <string>
#include <vector>

class Table {
 private:
  std::mutex __put_mutex, __take_mutex;
  std::condition_variable __cv;
  std::mutex __mutex;
  std::unique_ptr<std::string[]> buffer;
  int n_dish;
  int tail, head, count;

 public:
  explicit Table(int dish_size)
      : n_dish(dish_size), tail(0), head(0), count(0) {
    buffer = std::make_unique<std::string[]>(n_dish);
  }
  void put(std::string name, std::string cake);
  std::string take(std::string name);
};

class Counter {
 private:
  int count = 0;
  std::mutex __mutex;

 public:
  int next_id();
};

void thread_func_maker(std::weak_ptr<Table> table, std::string name,
                       std::weak_ptr<Counter> cake_id);
void thread_func_eater(std::weak_ptr<Table> table, std::string name);
