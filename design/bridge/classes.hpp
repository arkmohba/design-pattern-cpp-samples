#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

class DisplayImpl {
 public:
  virtual void raw_open() = 0;
  virtual void raw_print() = 0;
  virtual void raw_close() = 0;
};

using DisplayImplPtr = std::unique_ptr<DisplayImpl>;

class Display {
 private:
  DisplayImplPtr impl;

 public:
  explicit Display(DisplayImplPtr impl_) { impl = std::move(impl_); }
  void open() { impl->raw_open(); }
  void print() { impl->raw_print(); }
  void close() { impl->raw_close(); }
  void display() {
    open();
    print();
    close();
  }
};

using DisplayPtr = std::unique_ptr<Display>;

class CountDisplay : public Display {
 public:
  explicit CountDisplay(DisplayImplPtr impl_) : Display(std::move(impl_)) {}
  void multi_display(int times) {
    open();
    for (int i = 0; i < times; i++) {
      print();
    }
    close();
  }
};

class StringDisplayImpl : public DisplayImpl {
 private:
  std::string target;
  int width;

  void print_line() {
    std::cout << "+";
    for (int i = 0; i < width; i++) {
      std::cout << "-";
    }
    std::cout << "+" << std::endl;
  }

 public:
  explicit StringDisplayImpl(std::string str_)
      : target(str_), width(str_.length()) {}
  void raw_open() { print_line(); }
  void raw_print() { std::cout << "|" << target << "|" << std::endl; }
  void raw_close() { print_line(); }
};
