#include <memory>
#include <mutex>
#include <string>

class Person {
 private:
  const std::string __name;
  const std::string __address;

 public:
  Person(std::string name, std::string address)
      : __name(name), __address(address) {}
  std::string get_name() { return __name; }
  std::string get_address() { return __address; }
  std::string to_string();
};

void thread_func_show(std::shared_ptr<Person> person);
