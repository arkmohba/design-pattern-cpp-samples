#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

class Trouble {
 private:
  int number = 0;

 public:
  explicit Trouble(int number_) : number(number_) {}
  int get_number() const { return number; }
  std::string to_string();
};
using TroublePtr = std::weak_ptr<Trouble>;

class Support;
using SupportPtr = std::weak_ptr<Support>;

class Support {
 private:
  std::string name;
  SupportPtr next;

 protected:
  virtual bool resolve(TroublePtr trouble) = 0;
  void done(TroublePtr trouble);
  void fail(TroublePtr trouble);

 public:
  explicit Support(std::string name_) : name(name_) {}
  SupportPtr set_next(SupportPtr next);
  void support(TroublePtr trouble);
  std::string to_string() { return "[" + name + "]"; }
};

class NoSupport : public Support {
 protected:
  bool resolve(TroublePtr trouble) { return false; }

 public:
  explicit NoSupport(std::string name_) : Support(name_) {}
};

class LimitSupport : public Support {
 private:
  int limit;

 protected:
  bool resolve(TroublePtr trouble);

 public:
  LimitSupport(std::string name, int limit_) : Support(name), limit(limit_) {}
};

class OddSupport : public Support {
 protected:
  bool resolve(TroublePtr trouble);

 public:
  OddSupport(std::string name) : Support(name) {}
};

class SpecialSupport : public Support {
 private:
  int number;

 protected:
  bool resolve(TroublePtr trouble);

 public:
  SpecialSupport(std::string name, int number_)
      : Support(name), number(number_) {}
};
