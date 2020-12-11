#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

static const int sleep_time_us = 100 * 1000;

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Usage: main_app digits" << endl;
    cout << "Example: main_app 1212123" << endl;
    return 0;
  }
  // cout << argv[1] << endl;
  BigString bs(argv[1]);
  bs.print();
  return 0;
}
