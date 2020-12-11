#include "classes.hpp"

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <streambuf>
#include <string>

using namespace std;

BigChar::BigChar(char char_name_) : char_name(char_name_) {

  stringstream ss;
  ss << "../big" << char_name << ".txt";
  auto file_path = ss.str();

  ifstream t(file_path);
  stringstream buffer;
  buffer << t.rdbuf();
  font_data = buffer.str();
}

void BigChar::print() { cout << font_data << endl; }

std::shared_ptr<BigCharFactory> BigCharFactory::singleton =
    shared_ptr<BigCharFactory>(new BigCharFactory());

BigCharPtr BigCharFactory::get_big_char(char char_name) {
  shared_ptr<BigChar> bc;

  auto it = pool.find(char_name);
  if (it == pool.end()) {
    bc = make_shared<BigChar>(char_name);
    pool[char_name] = bc;
  } else {
    bc = pool.at(char_name);
  }
  return bc;
}

BigString::BigString(string str){
  auto factory = BigCharFactory::get_instance();
  for (auto c: str) {
    big_chars.push_back(factory.lock()->get_big_char(c));
  }
}

void BigString::print() {
  for (auto bc: big_chars) {
    bc.lock()->print();
  }
}
