#include "classes.hpp"

#include <unistd.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void MacroCommand::execute() {
  for (auto i = 0; i < commands.size(); i++) {
    commands[i]->execute();
  }
}

void MacroCommand::append(CommandPtr cmd) {
  // 自身の場合はスタックしない
  if (cmd.get() == this) {
    return;
  }
  commands.push_back(cmd);
  return;
}


void MacroCommand::undo() {
  if (!commands.empty()) {
    commands.pop_back();
  }
}


void DrawCanvas::draw(int x) {
  for (int i = 0; i < x; i++) {
    cout << " ";
  }
  cout << "*" << endl;
}