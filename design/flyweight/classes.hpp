#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

class BigChar {
 private:
  char char_name;
  std::string font_data;

 public:
  BigChar(char char_name_);
  void print();
};

using BigCharPtr = std::weak_ptr<BigChar>;

class BigCharFactory;
using BigCharFactoryPtr = std::weak_ptr<BigCharFactory>;

class BigCharFactory {
 private:
  std::map<char, std::shared_ptr<BigChar>> pool;
  static std::shared_ptr<BigCharFactory> singleton;
  BigCharFactory() {}

 public:
  static BigCharFactoryPtr get_instance() { return singleton; }
  BigCharPtr get_big_char(char char_name);
};

class BigString {
private:
  std::vector<BigCharPtr> big_chars;
public:
  explicit BigString(std::string str);
  void print();
};