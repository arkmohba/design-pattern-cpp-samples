#include "classes.hpp"

#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

static const int sleep_time_us = 100 * 1000;

using namespace std;

void NumberGenerator::delete_observer(ObserverPtr observer) {
  for (auto it = observers.begin(); it != observers.end(); it++) {
    if (it->lock() == observer.lock()) {
      // 削除時は要素を抜いた次のイテレータが来る
      it = observers.erase(it);
    } else {
      it++;
    }
  }
}

void NumberGenerator::notify_observers() {
  for (auto observer : observers) {
    observer.lock()->update(weak_from_this());
  }
}

void RandomNumberGenerator::execute() {
  for (int i = 0; i < 20; i++) {
    number = random.get_val(0, 50);
    notify_observers();
  }
}

void DigitObserver::update(NumberGeneratorPtr generator) {
  cout << "DigitObserver:" << generator.lock()->get_number() << endl;
  usleep(sleep_time_us);
}

void GraphObserver::update(NumberGeneratorPtr generator) {
  cout << "GraphObserver:";
  int count = generator.lock()->get_number();
  for (int i = 0; i < count; i++) {
    cout << "*";
  }
  cout << endl;
  usleep(sleep_time_us);
}
