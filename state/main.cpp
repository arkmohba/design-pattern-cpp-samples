#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

static const int sleep_time_us = 100 * 1000;

using namespace std;

class IntRangeRandom {
 private:
  std::mt19937 random_val;

 public:
  IntRangeRandom() : random_val(std::random_device()()) {}
  int get_val(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(random_val);
  }
};

static const vector<string> PERFORMS = {"use", "alarm", "phone", "exit"};

int main() {
  shared_ptr<SafeFrame> frame = make_shared<SafeFrame>("State Sample");
  IntRangeRandom random;
  while (true) {
    for (int hour = 0; hour < 24; hour++) {
      frame->set_clock(hour);
      int val = random.get_val(0, 3);
      if (hour == val) {
        auto action = PERFORMS[val];
        frame->action_performed(action);
      }
      usleep(sleep_time_us);
    }
  }
  return 0;
}
