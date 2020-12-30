#include "classes.hpp"

#include <unistd.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::shared_ptr<DayState> DayState::singleton =
    shared_ptr<DayState>(new DayState());

std::shared_ptr<NightState> NightState::singleton =
    shared_ptr<NightState>(new NightState());

void DayState::do_clock(ContextPtr context, int hour) {
  if (hour < 9 || 17 <= hour) {
    context.lock()->change_state(NightState::get_instance());
  }
}

void DayState::do_use(ContextPtr context) {
  context.lock()->record_log("金庫使用（昼間）");
}

void DayState::do_alarm(ContextPtr context) {
  context.lock()->call_security_center("非常ベル（昼間）");
}

void DayState::do_phone(ContextPtr context) {
  context.lock()->call_security_center("通常の通話（昼間）");
}

void NightState::do_clock(ContextPtr context, int hour) {
  if (9 <= hour && hour < 17) {
    context.lock()->change_state(DayState::get_instance());
  }
}

void NightState::do_use(ContextPtr context) {
  context.lock()->record_log("非常：夜間の金庫使用");
}

void NightState::do_alarm(ContextPtr context) {
  context.lock()->call_security_center("非常ベル（夜間）");
}

void NightState::do_phone(ContextPtr context) {
  context.lock()->call_security_center("夜間の通話録音");
}

void SafeFrame::action_performed(string action) {
  if (action == "use") {
    state.lock()->do_use(weak_from_this());
  } else if (action == "alarm") {
    state.lock()->do_alarm(weak_from_this());
  } else if (action == "phone") {
    state.lock()->do_phone(weak_from_this());
  } else if (action == "exit") {
    return;
  } else {
    cout << "?" << endl;
  }
}

void SafeFrame::set_clock(int hour) {
  stringstream clock_ss;
  clock_ss << "現在時刻は";
  if (hour < 10) {
    clock_ss << "0" << hour << ":00";
  } else {
    clock_ss << hour << ":00";
  }
  auto clock_string = clock_ss.str();
  cout << clock_string << endl;
  text_clock = clock_string;

  state.lock()->do_clock(weak_from_this(), hour);
}

void SafeFrame::change_state(StatePtr state_) {
  cout << state.lock()->to_string() << "から" << state_.lock()->to_string()
       << "へ状態が変化しました。" << endl;
  state = state_;
}

void SafeFrame::call_security_center(string msg) {
  stringstream tmp;
  tmp << "call! " << msg << endl;
  text_screen += tmp.str();
  cout << text_screen << endl;
}

void SafeFrame::record_log(string msg) {
  stringstream tmp;
  tmp << "record ..." << msg << endl;
  text_screen += tmp.str();
  cout << text_screen << endl;
}