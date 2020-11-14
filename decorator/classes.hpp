#pragma once
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

class Display {
 public:
  virtual int get_columns() = 0;
  virtual int get_rows() = 0;
  virtual std::string get_row_text(int row) = 0;
  void show() {
    for (int i = 0; i < get_rows(); i++) {
      std::cout << get_row_text(i) << std::endl;
    }
  }
};

using DisplayPtr = std::shared_ptr<Display>;

class StringDisplay : public Display {
 private:
  std::string str;

 public:
  explicit StringDisplay(std::string str_) : str(str_) {}
  int get_columns() { return str.length(); }
  int get_rows() { return 1; }
  std::string get_row_text(int row) {
    if (row == 0) {
      return str;
    } else {
      return "";
    }
  }
};

class Border : public Display {
 protected:
  DisplayPtr display;
  explicit Border(DisplayPtr display_) : display(display_) {}
};

class SideBorder : public Border {
 private:
  char border_char;

 public:
  SideBorder(DisplayPtr display_, char border_char_)
      : Border(display_), border_char(border_char_) {}
  int get_columns() { return 1 + display->get_columns() + 1; }
  int get_rows() { return display->get_rows(); }
  std::string get_row_text(int row) {
    std::stringstream ss;
    ss << border_char << display->get_row_text(row) << border_char;
    return ss.str();
  }
};

class FullBorder : public Border {
 private:
  std::string make_line(char ch, int count);

 public:
  explicit FullBorder(DisplayPtr display_) : Border(display_) {}
  int get_columns() { return 1 + display->get_columns() + 1; }
  int get_rows() { return 1 + display->get_rows() + 1; }
  std::string get_row_text(int row);
};