/*classes header*/

#pragma once

#include <string>
#include <vector>

class Product {
 public:
  virtual void use() = 0;
};

class Factory {
 public:
  Product* create(std::string owner);

 protected:
  virtual Product* create_product(std::string owner) = 0;
  virtual void register_product(Product* product) = 0;
};

class IDCard : public Product {
 private:
  std::string owner;

 public:
  explicit IDCard(std::string owner);
  void use();
  std::string get_owner() { return owner; }
};

class IDCardFactory : public Factory {
 private:
  std::vector<std::string> owners;

 protected:
  Product* create_product(std::string owner);
  void register_product(Product* product);

 public:
  std::vector<std::string> get_owners() { return owners; }
};