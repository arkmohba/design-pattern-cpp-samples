#include "classes.hpp"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string Trouble::to_string() {
  stringstream ss;
  ss << "[Trouble" << number << "]";
  return ss.str();
}

void Support::done(TroublePtr trouble) {
  auto t = trouble.lock();
  cout << t->to_string() << " is resolved by" << to_string() << "." << endl;
}

void Support::fail(TroublePtr trouble) {
  auto t = trouble.lock();
  cout << t->to_string() << " cannot be resolved." << endl;
}

SupportPtr Support::set_next(SupportPtr next_) {
  next = next_;
  return next;
}

void Support::support(TroublePtr trouble) {
  if (resolve(trouble)) {
    done(trouble);
  } else if (!next.expired()) {
    auto next_locked = next.lock();
    next_locked->support(trouble);
  } else {
    fail(trouble);
  }
}

bool LimitSupport::resolve(TroublePtr trouble) {
  auto t = trouble.lock();
  if (t->get_number() < limit) {
    return true;
  } else {
    return false;
  }
}

bool OddSupport::resolve(TroublePtr trouble) {
  auto t = trouble.lock();
  if (t->get_number() % 2 == 1) {
    return true;
  } else {
    return false;
  }
}

bool SpecialSupport::resolve(TroublePtr trouble) {
  auto t = trouble.lock();
  if (t->get_number() == number) {
    return true;
  } else {
    return false;
  }
}
