#pragma once
#include <iostream>
#include <memory>
#include <deque>
#include <string>
#include <utility>
#include <vector>

class Command {
 public:
  virtual void execute() = 0;
};

using CommandPtr = std::shared_ptr<Command>;

class MacroCommand : public Command {
 private:
  std::deque<CommandPtr> commands;

 public:
  void execute();
  void append(CommandPtr cmd);
  void undo();
  void clear() {
    while (!commands.empty()) commands.pop_back();
  }
};

class Point {
 public:
  explicit Point(int x_): x(x_) {}
  int x;
};
class Drawable {
 public:
  virtual void draw(int x) = 0;
};

class DrawCommand : public Command {
 protected:
  std::weak_ptr<Drawable> drawable;

 private:
  Point position;

 public:
  DrawCommand(std::weak_ptr<Drawable> drawable_, Point position_)
      : drawable(drawable_), position(position_) {}
  void execute() { drawable.lock()->draw(position.x); }
};

class DrawCanvas : public Drawable {
 private:
  char point_ch;
  std::weak_ptr<MacroCommand> history;

 public:
  explicit DrawCanvas(std::weak_ptr<MacroCommand> history_) {
    history = history_;
  }
  void paint() { history.lock()->execute(); }
  void draw(int x);
};
