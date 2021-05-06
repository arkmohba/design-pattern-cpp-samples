#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  cout << "main BEGIN" << endl;
  auto host = make_unique<Host>();
  auto data1 = host->request(10, 'A');
  auto data2 = host->request(20, 'B');
  auto data3 = host->request(30, 'C');

  cout << "main other job BEGIN" << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << "main other job END" << endl;

  cout << "data1 = " << data1->get_content() << endl;
  cout << "data2 = " << data2->get_content() << endl;
  cout << "data3 = " << data3->get_content() << endl;


  cout << "main END" << endl;
  return 0;
}
