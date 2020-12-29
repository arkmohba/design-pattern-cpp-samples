#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"
using namespace std;

int main() {
  auto history = make_shared<MacroCommand>();
  auto canvas = make_shared<DrawCanvas>(history);
  int len = 10;
  for (int i = 0; i < len; i++) {
    auto cmd = make_shared<DrawCommand>(canvas, Point(i));
    history->append(cmd);
    cmd->execute();
  }
  for (int i = 0; i < len; i++) {
    history->execute();
    history->undo();
  }
  return 0;
}
