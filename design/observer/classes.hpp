#pragma once
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

class NumberGenerator;
using NumberGeneratorPtr = std::weak_ptr<NumberGenerator>;

class Observer {
 public:
  virtual void update(NumberGeneratorPtr generator) = 0;
};

using ObserverPtr = std::weak_ptr<Observer>;

class NumberGenerator : public std::enable_shared_from_this<NumberGenerator> {
 private:
  std::vector<ObserverPtr> observers;

 public:
  void add_observer(ObserverPtr observer) { observers.push_back(observer); }
  void delete_observer(ObserverPtr observer);
  void notify_observers();
  virtual int get_number() = 0;
  virtual void execute() = 0;
};

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

using NumberGeneratorPtr = std::weak_ptr<NumberGenerator>;

class RandomNumberGenerator : public NumberGenerator {
 private:
  IntRangeRandom random;
  int number;

 public:
  int get_number() { return number; }
  void execute();
};

class DigitObserver : public Observer {
 public:
  void update(NumberGeneratorPtr generator);
};

class GraphObserver : public Observer {
 public:
  void update(NumberGeneratorPtr generator);
};
