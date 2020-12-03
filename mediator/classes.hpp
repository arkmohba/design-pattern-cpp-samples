#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Mediator {
 public:
  virtual void create_colleagues() = 0;
  virtual void colleague_changed() = 0;
};

using MediatorPtr = std::weak_ptr<Mediator>;

class Colleague {
 public:
  virtual void set_mediator(MediatorPtr mediator) = 0;
  virtual void set_colleague_enabled(bool enabled) = 0;
};

class ColleagueButton : public Colleague {
 private:
  MediatorPtr mediator;
  std::string caption;
  bool is_enabled = true;
  bool is_pushed = false;

 public:
  ColleagueButton(std::string caption_) : caption(caption) {}
  void set_mediator(MediatorPtr mediator_) { mediator = mediator_; }
  void set_colleague_enabled(bool enabled) { is_enabled = enabled; }
  void clicked() {
    if (is_enabled) {
      is_pushed = !is_pushed;
    } else {
      std::cout << "button:" << caption << "is not enabled." << std::endl;
    }
  }
  bool get_state() {return is_pushed;}
};

class ColleagueTextField : public Colleague {
 private:
  MediatorPtr mediator;
  std::string text;
  bool is_enabled = false;

 public:
  explicit ColleagueTextField(std::string text_) : text(text_) {}
  void set_mediator(MediatorPtr mediator_) { mediator = mediator_; }
  void set_colleague_enabled(bool enabled) { is_enabled = enabled; }
  void set_text(std::string new_text) {
    if (is_enabled) {
      text = new_text;
      auto m = mediator.lock();
      m->colleague_changed();
    }
  }
  std::string get_text() { return text; }
};

class ColleagueCheckBox;

class CheckBoxMediator {
 private:
  std::vector<std::weak_ptr<ColleagueCheckBox>> check_boxes;

 public:
  void set_checkbox(std::weak_ptr<ColleagueCheckBox> check) {
    check_boxes.push_back(check);
  }
  void colleague_changed(std::string name);
};

class ColleagueCheckBox : public Colleague,
                          public std::enable_shared_from_this<ColleagueCheckBox> {
 private:
  MediatorPtr mediator;
  std::weak_ptr<CheckBoxMediator> cb_mediator;
  std::string caption;
  bool state = false;
  bool is_enabled = true;

 public:
  ColleagueCheckBox(std::string caption_, bool state_)
      : caption(caption_), state(state_) {}
  void set_mediator(MediatorPtr mediator_) { mediator = mediator_; }
  void set_cb_mediator(std::weak_ptr<CheckBoxMediator> cb_mediator_) {
    cb_mediator = cb_mediator_;
  }
  void set_colleague_enabled(bool enabled) { is_enabled = enabled; }
  void check() {
    if (is_enabled) {
      state = true;
      auto cbm = cb_mediator.lock();
      cbm->colleague_changed(caption);
      
      auto m = mediator.lock();
      if (m == nullptr) {std::cout << "mediator is NULL" << std::endl;}
      m->colleague_changed();
    }
  }
  void check(bool state_) { state = state_; }
  bool get_state() { return state; }
  std::string get_caption() { return caption; }
};

class LoginFrame : public Mediator, public std::enable_shared_from_this<LoginFrame> {
 private:
  std::shared_ptr<CheckBoxMediator> cb_mediator;
  std::string title;
  void userpass_changed();

 public:
  std::shared_ptr<ColleagueCheckBox> check_guest;
  std::shared_ptr<ColleagueCheckBox> check_login;
  std::shared_ptr<ColleagueTextField> text_user;
  std::shared_ptr<ColleagueTextField> text_pass;
  std::shared_ptr<ColleagueButton> button_ok;
  std::shared_ptr<ColleagueButton> button_cancel;
  explicit LoginFrame(std::string title_);
  void build();
  void create_colleagues();
  void colleague_changed();
  void show_state();
};
