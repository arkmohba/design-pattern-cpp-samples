#pragma once
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Context {
 private:
  std::stringstream tokenizer;
  std::string current_token_;

 public:
  Context(std::string text);
  void skip_token(std::string target);
  std::string current_token();
  int current_number();
  std::string next_token();
};
using ContextPtr = std::weak_ptr<Context>;

class Node {
 public:
  virtual void parse(ContextPtr context) = 0;
  virtual std::string to_string() = 0;
};

using NodePtr = std::shared_ptr<Node>;

class ProgramNode : public Node {
 private:
  NodePtr command_list_node;

 public:
  void parse(ContextPtr context);
  std::string to_string();
};

class CommandListNode : public Node {
 private:
  std::vector<NodePtr> command_list;

 public:
  void parse(ContextPtr context);
  std::string to_string();
};

class CommandNode : public Node {
 private:
  NodePtr node;

 public:
  void parse(ContextPtr context);
  std::string to_string();
};

class RepeatCommandNode : public Node {
 private:
  int number;
  NodePtr command_list_node;

 public:
  void parse(ContextPtr context);
  std::string to_string();
};

class PrimitiveCommandNode : public Node {
 private:
  std::string name;

 public:
  void parse(ContextPtr context);
  std::string to_string();
};