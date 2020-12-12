#include "classes.hpp"

#include <unistd.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void Printer::heavy_job(string msg) {
  cout << msg;
  for (int i = 0; i < 5; i++) {
    sleep(1);
    cout << ".";
  }
  cout << "完了。" << endl;
}

Printer::Printer(std::string name_): name(name_) {
  stringstream ss;
  ss << "Printerのインスタンス（" << name << "）を生成中";
  heavy_job(ss.str());
}

void Printer::print(string str) {
  cout << "=== " + name + " ===" << endl;
  cout << str << endl;
}

void PrinterProxy::realize() {
  if (real == nullptr) {
    real = make_unique<Printer>(name);
  }
}

void PrinterProxy::set_printer_name(string name_) {
  if (real != nullptr) {
    real->set_printer_name(name_);
  }
  name = name_;
}

void PrinterProxy::print(string str) {
  // ここで初めて生成
  realize();
  // 実行
  real->print(str);
}
