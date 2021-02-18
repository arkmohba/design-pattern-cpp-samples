#include <memory>
#include <mutex>
#include <string>

class Gate {
 private:
  int counter = 0;
  std::string name = "Nobody";
  std::string address = "Nowhere";
  void check();

 public:
  std::string to_string();
  void pass(std::string name_, std::string address_);
  int get_counter() { return counter; }
};

void thread_func(std::shared_ptr<Gate> gate, std::string name,
                 std::string address);
