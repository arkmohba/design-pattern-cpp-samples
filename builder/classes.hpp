#pragma once
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Builder {
 public:
  virtual void makeTitle(std::string s) = 0;
  virtual void makeString(std::string s) = 0;
  virtual void makeItems(std::vector<std::string>) = 0;
  virtual void close() = 0;
};

using BuilderPtr = std::shared_ptr<Builder>;

class Director {
 private:
  BuilderPtr builder;

 public:
  explicit Director(BuilderPtr builder);
  void construct();
};

class TextBuilder : public Builder {
 private:
  std::ostringstream buffer;

 public:
  void makeTitle(std::string s);
  void makeString(std::string s);
  void makeItems(std::vector<std::string>);
  void close();
  std::string getResult() {
    buffer << std::flush;
    return buffer.str();
  }
};

class HTMLBuilder : public Builder {
 private:
  std::string filename;
  std::ofstream ofs;

 public:
  void makeTitle(std::string s);
  void makeString(std::string s);
  void makeItems(std::vector<std::string>);
  void close();
  std::string getResult() { return filename; }
};
