#pragma once
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

class Gamer;

class Memento {
 private:
  int money;
  std::vector<std::string> fruits;
  explicit Memento(int money_) : money(money_) {}
  std::vector<std::string> get_fruits() { return fruits; }

 public:
  friend Gamer;
  int get_money() { return money; }
  void add_fruit(std::string fruit) { fruits.push_back(fruit); }
};

using MementoPtr = std::shared_ptr<Memento>;

class IntRangeRandom {
 private:
  std::mt19937 random_val;

 public:
  IntRangeRandom() : random_val(std::random_device()()) {}
  int get_val(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(random_val);
  }
};

class Gamer {
 private:
  int money;
  std::vector<std::string> fruits;
  IntRangeRandom random;
  static std::vector<std::string> fruitsname;
  std::string get_fruit();

 public:
  explicit Gamer(int money_);
  int get_money() { return money; }
  void bet();
  MementoPtr create_memento();
  void restore_memento(std::weak_ptr<Memento> w_memento);
  std::string to_string();
};
