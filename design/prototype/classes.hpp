#pragma once
#include <map>
#include <string>

class Product {
 public:
  virtual void use(std::string s) = 0;
  virtual Product* create_clone() = 0;
};

class Manager {
 private:
  std::map<std::string, Product*> showcase{};

 public:
  Product* create(std::string proto_name);

  void register_proto(std::string name, Product* proto) {
    showcase[name] = proto;
  }
};

class MessageBox : public Product {
 private:
  char decochar;

 public:
  explicit MessageBox(char decochar_) : decochar(decochar_) {}
  void use(std::string s);
  Product* create_clone();
};

class UnderlinePen : public Product {
 private:
  char ulchar;

 public:
  explicit UnderlinePen(char ulchar_) : ulchar(ulchar_) {}
  void use(std::string s);
  Product* create_clone();
};