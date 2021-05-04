#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  cout << "main BEGIN" << endl;
  auto host = make_shared<Host>();
  host->request(10, 'A');
  host->request(20, 'B');
  host->request(30, 'C');
  cout << "main END" << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  return 0;
}
