#include "classes.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

void CheckBoxMediator::colleague_changed(string name) {
  for (auto wp_check : check_boxes) {
    auto check = wp_check.lock();
    if (check->get_caption() == name) continue;
    check->check(false);
  }
}

LoginFrame::LoginFrame(string title_) : title(title_) {}

void LoginFrame::build() {
  create_colleagues();
  colleague_changed();
}

void LoginFrame::create_colleagues() {
  check_guest = make_shared<ColleagueCheckBox>("Guest", true);
  check_login = make_shared<ColleagueCheckBox>("Login", false);
  text_user = make_shared<ColleagueTextField>("");
  text_pass = make_shared<ColleagueTextField>("");
  button_ok = make_shared<ColleagueButton>("OK");
  button_cancel = make_shared<ColleagueButton>("Cancel");

  auto weak_this = weak_from_this();
  if (weak_this.lock() == nullptr) {
    cout << "weak_this is Nullptr" << endl;
  }
  check_guest->set_mediator(weak_from_this());
  check_login->set_mediator(weak_from_this());
  text_user->set_mediator(weak_from_this());
  text_pass->set_mediator(weak_from_this());
  button_ok->set_mediator(weak_from_this());
  button_cancel->set_mediator(weak_from_this());

  cb_mediator = make_shared<CheckBoxMediator>();
  cb_mediator->set_checkbox(check_guest);
  cb_mediator->set_checkbox(check_login);
  check_guest->set_cb_mediator(cb_mediator);
  check_login->set_cb_mediator(cb_mediator);
}

void LoginFrame::colleague_changed() {
  if (check_guest->get_state()) {
    text_user->set_colleague_enabled(false);
    text_pass->set_colleague_enabled(false);
    button_ok->set_colleague_enabled(true);
  } else {
    text_user->set_colleague_enabled(true);
    userpass_changed();
  }
}

void LoginFrame::userpass_changed() {
  if (!text_user->get_text().empty()) {
    text_pass->set_colleague_enabled(true);
    if (!text_pass->get_text().empty()) {
      button_ok->set_colleague_enabled(true);
    } else {
      button_ok->set_colleague_enabled(false);
    }
  } else {
    text_pass->set_colleague_enabled(false);
    button_ok->set_colleague_enabled(false);
  }
}

void LoginFrame::show_state() {
  auto ch_guest = check_guest;
  auto ch_login = check_login;
  auto user = text_user;
  auto pass = text_pass;
  auto ok = button_ok;
  auto cancel = button_cancel;

  cout << "=======================================================" << endl;
  cout << "check box guest"
       << ":" << ch_guest->get_state() << endl;
  cout << "check box login"
       << ":" << ch_login->get_state() << endl;
  cout << "text user"
       << ":" << user->get_text() << endl;
  cout << "text pass"
       << ":" << pass->get_text() << endl;
  cout << "button ok"
       << ":" << ok->get_state() << endl;
  cout << "button cancel"
       << ":" << cancel->get_state() << endl;
  cout << "=======================================================" << endl;
}