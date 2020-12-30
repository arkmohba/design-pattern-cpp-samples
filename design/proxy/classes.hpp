#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Printable {
 public:
  virtual void set_printer_name(std::string name_) = 0;
  virtual std::string get_printer_name() = 0;
  virtual void print(std::string str) = 0;
};

class Printer : public Printable {
 private:
  std::string name;
  void heavy_job(std::string msg);

 public:
  Printer() { heavy_job("Printerのインスタンスを生成中"); }
  explicit Printer(std::string name_);
  void set_printer_name(std::string name_) { name = name_; }
  std::string get_printer_name() { return name; }
  void print(std::string str);
};

class PrinterProxy : public Printable {
 private:
  std::string name;
  std::unique_ptr<Printer> real;
  void realize();

 public:
  PrinterProxy() {}
  explicit PrinterProxy(std::string name_) : name(name_) {}
  void set_printer_name(std::string name_);
  std::string get_printer_name() { return name; }
  void print(std::string str);
};