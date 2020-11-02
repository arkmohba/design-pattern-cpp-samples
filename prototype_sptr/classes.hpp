#pragma once
#include <map>
#include <memory>
#include <string>
#include <utility>

class Product {
 public:
  virtual void use(std::string s) = 0;
  virtual std::unique_ptr<Product> create_clone() = 0;
};

// Productのunique_ptrを定義
using ProductPtr = std::unique_ptr<Product>;

class Manager {
 private:
  std::map<std::string, ProductPtr> showcase{};

 public:
  ProductPtr create(std::string proto_name);

  void register_proto(std::string name, ProductPtr proto) {
    showcase[name] = std::move(proto);
  }
};

class MessageBox : public Product {
 private:
  char decochar;

 public:
  explicit MessageBox(char decochar_) : decochar(decochar_) {}
  void use(std::string s);
  ProductPtr create_clone();
};

class UnderlinePen : public Product {
 private:
  char ulchar;

 public:
  explicit UnderlinePen(char ulchar_) : ulchar(ulchar_) {}
  void use(std::string s);
  ProductPtr create_clone();
};