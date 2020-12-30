#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

class Visitor;
using VisitorPtr = std::shared_ptr<Visitor>;

class Element {
 public:
  virtual void accept(VisitorPtr visitor) = 0;
};

class Entry;
using EntryPtr = std::shared_ptr<Entry>;

class Entry : public std::enable_shared_from_this<Entry>, public Element {
 public:
  virtual std::string get_name() = 0;
  virtual int get_size() = 0;
  virtual std::shared_ptr<Entry> add(std::shared_ptr<Entry> entry) {
    throw "Exception : not implemented error.\n";
    return nullptr;
  }
  std::string to_string() {
    return get_name() + " (" + std::to_string(get_size()) + ")";
  }
};


class File : public Entry {
 private:
  std::string name;
  int size;

 public:
  explicit File(std::string name_, int size_) : name(name_), size(size_) {}
  std::string get_name() { return name; }
  int get_size() { return size; }
  void accept(VisitorPtr v);
};

class Directory : public Entry {
 private:
  std::string name;
  std::vector<EntryPtr> directory;

 public:
  explicit Directory(std::string name_) : name(name_), directory() {}
  std::string get_name() { return name; }
  int get_size();
  EntryPtr add(EntryPtr entry);
  const std::vector<EntryPtr>& get_entries() { return directory;}
  void accept(VisitorPtr v);
};

class Visitor : public std::enable_shared_from_this<Visitor>  {
 public:
  virtual void visit(File* file) = 0;
  virtual void visit(Directory* dir) = 0;
};

class ListVisitor : public Visitor {
 private:
  std::string current_dir = "";

 public:
  void visit(File* file);
  void visit(Directory* dir);
};
