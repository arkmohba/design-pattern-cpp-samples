/*classes header*/

#pragma once

#include <string>

class AbstractDisplay {
 public:
  virtual void open() = 0;
  virtual void print() = 0;
  virtual void close() = 0;
  void display();
};

class CharDisplay : public AbstractDisplay {
 private:
  char ch;

 public:
  explicit CharDisplay(char ch_);
  void open();
  void print();
  void close();
};

class StringDisplay : public AbstractDisplay {
 private:
  std::string str;
  std::string line = "+-----------------+";

 public:
  explicit StringDisplay(std::string target);
  void open();
  void print();
  void close();
};
