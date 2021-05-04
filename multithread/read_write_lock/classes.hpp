#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <string>

class ReadWriteLock {
 private:
  int reading_readears = 0;
  int waiting_writers = 0;
  int writing_writers = 0;
  bool prefer_writer = true;

  std::mutex rl_mutex, rul_mutex, wl_mutex, wul_mutex;
  std::mutex data_mutex;
  std::condition_variable cv;

 public:
  void read_lock();
  void read_unlock();
  void write_lock();
  void write_unlock();
};

class Data {
 private:
  ReadWriteLock __lock;
  std::string __buffer;
  std::string do_read();
  void do_write(char c);
  void slowly();

 public:
  explicit Data(int size);
  std::string read();
  void write(char c);
};

void thread_func_writer(std::weak_ptr<Data> data, std::string filler);
void thread_func_reader(std::weak_ptr<Data> data, std::string name);
