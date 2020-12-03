#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  auto frame = make_shared<LoginFrame>("Mediator sample");
  frame->build();
  frame->show_state();
  frame->text_user->set_text("foobar");
  frame->show_state();
  frame->check_login->check();
  frame->text_user->set_text("foobar");
  frame->show_state();
  frame->text_user->set_text("");
  frame->text_pass->set_text("abcdef");
  frame->show_state();
  frame->text_user->set_text("foobar");
  frame->text_pass->set_text("abcdef");
  frame->show_state();
  return 0;
}
