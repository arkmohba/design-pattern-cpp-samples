#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> split(const std::string& input, char delimiter);

class Property {
 private:
  std::map<std::string, std::string> accounts;

 public:
  void load(std::string file_path);
  std::string get_properties(std::string mail_address) {
    return accounts[mail_address];
  }
};

using PropertyPtr = std::shared_ptr<Property>;

class Database {
 private:
  Database() {}

 public:
  static PropertyPtr get_properties(std::string dbname);
};

class HtmlWriter {
 private:
  std::weak_ptr<std::ofstream> writer;

 public:
  explicit HtmlWriter(std::shared_ptr<std::ofstream> writer_)
      : writer(writer_) {}
  void title(std::string title);
  void paragraph(std::string msg);
  void link(std::string href, std::string caption);
  void mailto(std::string mailaddr, std::string username);
  void close();
};

class PageMaker {
 public:
  static void make_welcome_page(std::string mailaddr, std::string filename);
};
