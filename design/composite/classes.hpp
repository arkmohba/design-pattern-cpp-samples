#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

class Entry : public std::enable_shared_from_this<Entry> {
 public:
  virtual std::string get_name() = 0;
  virtual int get_size() = 0;
  virtual std::shared_ptr<Entry> add(std::shared_ptr<Entry> entry) {
    throw "Exception : not implemented error.\n";
    return nullptr;
  }
  void print_list() { print_list(""); }
  virtual void print_list(std::string str) = 0;
  std::string to_string() {
    return get_name() + " (" + std::to_string(get_size()) + ")";
  }
};

using EntryPtr = std::shared_ptr<Entry>;

class File : public Entry {
 private:
  std::string name;
  int size;

 public:
  void print_list(std::string prefix) {
    std::cout << prefix << "/" << to_string() << std::endl;
  }
  explicit File(std::string name_, int size_) : name(name_), size(size_) {}
  std::string get_name() { return name; }
  int get_size() { return size; }
};

class Directory : public Entry {
 private:
  std::string name;
  std::vector<EntryPtr> directory;

 public:
  void print_list(std::string prefix);
  explicit Directory(std::string name_) : name(name_), directory() {}
  std::string get_name() { return name; }
  int get_size();
  EntryPtr add(EntryPtr entry);
};
