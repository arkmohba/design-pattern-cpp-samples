#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>

class Data {
 private:
  std::mutex __mutex;  // __contentと__changedを守るmutex
  const std::string __filename;
  std::string __content;
  bool __changed = true;

  void do_save(std::string user);

 public:
  Data(std::string filename, std::string content)
      : __filename(filename), __content(content), __changed(true) {}
  void change(std::string new_content);
  void save(std::string user);
};

void thread_func_saver(std::weak_ptr<Data> data, std::string name);
void thread_func_changer(std::weak_ptr<Data> data, std::string name);
