#include "classes.hpp"

#include <unistd.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>

using namespace std;

void Helper::slowly() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Helper::handle(int count, char c) {
  cout << "        handle(" << count << ", " << c << ") BEGIN" << endl;
  for (int i = 0; i < count; i++) {
    slowly();
    cout << c;
  }
  cout << endl;
  cout << "        handle(" << count << ", " << c << ") END" << endl;
}
void Host::request(int count, char c) {
  cout << "        request(" << count << ", " << c << ") BEGIN" << endl;
  thread th([count, c, this] { helper.handle(count, c); });
  th.detach();
  cout << "        request(" << count << ", " << c << ") END" << endl;
}
