#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  shared_ptr<NumberGenerator> generator = make_shared<RandomNumberGenerator>();
  shared_ptr<Observer> observer1 = make_shared<DigitObserver>();
  shared_ptr<Observer> observer2 = make_shared<GraphObserver>();
  generator->add_observer(observer1);
  generator->add_observer(observer2);
  generator->execute();
  return 0;
}
