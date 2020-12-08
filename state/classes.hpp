#pragma once
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

class State;
using StatePtr = std::weak_ptr<State>;

class Context : public std::enable_shared_from_this<Context> {
 public:
  virtual void set_clock(int hour) = 0;
  virtual void change_state(StatePtr state) = 0;
  virtual void call_security_center(std::string msg) = 0;
  virtual void record_log(std::string msg) = 0;
};
using ContextPtr = std::weak_ptr<Context>;

class State {
 public:
  virtual void do_clock(ContextPtr context, int hour) = 0;
  virtual void do_use(ContextPtr context) = 0;
  virtual void do_alarm(ContextPtr context) = 0;
  virtual void do_phone(ContextPtr context) = 0;
  virtual std::string to_string() = 0;
};

class DayState : public State {
 private:
  static std::shared_ptr<DayState> singleton;
  DayState() {}

 public:
  static StatePtr get_instance() { return singleton; }
  void do_clock(ContextPtr context, int hour);
  void do_use(ContextPtr context);
  void do_alarm(ContextPtr context);
  void do_phone(ContextPtr context);
  std::string to_string() { return "[昼間]"; }
};

class NightState : public State {
 private:
  static std::shared_ptr<NightState> singleton;
  NightState() {}

 public:
  static StatePtr get_instance() { return singleton; }
  void do_clock(ContextPtr context, int hour);
  void do_use(ContextPtr context);
  void do_alarm(ContextPtr context);
  void do_phone(ContextPtr context);
  std::string to_string() { return "[夜間]"; }
};

class SafeFrame : public Context {
 private:
  std::string title;
  StatePtr state;
  std::string text_clock;
  std::string text_screen;

 public:
  explicit SafeFrame(std::string title_) : title(title_) {
    state = DayState::get_instance();
  }
  void action_performed(std::string action);
  void set_clock(int hour);
  void change_state(StatePtr state);
  void call_security_center(std::string msg);
  void record_log(std::string msg);
};