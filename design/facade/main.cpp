#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  PageMaker::make_welcome_page("hyuki@hyuki.com", "welcome.html");
  return 0;
}
