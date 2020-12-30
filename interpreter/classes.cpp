#include "classes.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// <program> ::= program <command list>
void ProgramNode::parse(ContextPtr context) {
  string skip_token = "program";
  context.lock()->skip_token(skip_token);
  command_list_node = make_shared<CommandListNode>();
  command_list_node->parse(context);
}

string ProgramNode::to_string() {
  return "[program " + command_list_node->to_string() + "]";
}

// <command list> ::=<command>* end
void CommandListNode::parse(ContextPtr context_weak) {
  auto context = context_weak.lock();
  while (true) {
    if (context->current_token() == "") {
      throw runtime_error("Parse Error: Missing 'end'");
    } else if (context->current_token() == "end") {
      // リスト中のendは次のelse内で処理されるので、最後のendだけ処理する。
      context->skip_token("end");
      break;
    } else {
      NodePtr command_node = make_shared<CommandNode>();
      command_node->parse(context);
      command_list.push_back(command_node);
    }
  }
}

string CommandListNode::to_string() {
  if (command_list.size() == 0) {
    return "[]";
  }
  stringstream ss;
  ss << "[";
  ss << command_list[0]->to_string();
  for (int i = 1; i < command_list.size(); i++) {
    auto command = command_list[i];
    ss << " " << command->to_string();
  }
  ss << "]";
  return ss.str();
}

// <command> ::= <repeat command> | <primitive command>
void CommandNode::parse(ContextPtr context_weak) {
  auto context = context_weak.lock();
  if (context->current_token() == "repeat") {
    node = make_shared<RepeatCommandNode>();
    node->parse(context);
  } else {
    node = make_shared<PrimitiveCommandNode>();
    node->parse(context);
  }
}

string CommandNode::to_string() { return node->to_string(); }

// <repeat command> ::= repeat <number> <command list>
void RepeatCommandNode::parse(ContextPtr context_weak) {
  auto context = context_weak.lock();
  context->skip_token("repeat");
  number = context->current_number();
  context->next_token();
  command_list_node = make_shared<CommandListNode>();
  command_list_node->parse(context);
}

string RepeatCommandNode::to_string() {
  stringstream ss;
  ss << "repeat " << number << " " << command_list_node->to_string();
  return ss.str();
}

void PrimitiveCommandNode::parse(ContextPtr context_weak) {
  auto context = context_weak.lock();
  name = context->current_token();
  context->skip_token(name);
  if (name != "go" && name != "right" && name != "left") {
    throw std::runtime_error("Parse Error: " + name + " is undefined");
  }
}

string PrimitiveCommandNode::to_string() { return name; }

Context::Context(string text) {
  tokenizer.str(text);
  next_token();
}

std::string Context::next_token() {
  if (tokenizer.str().empty()) {
    current_token_ = "";
  } else {
    tokenizer >> current_token_;
  }
  return current_token_;
}

std::string Context::current_token() { return current_token_; }

void Context::skip_token(string token) {
  if (token != current_token_) {
    throw std::runtime_error("Parse Error: Warning: " + token +
                             " is expected, but " + current_token_ +
                             " is found.");
  }
  next_token();
}

int Context::current_number() {
  int number = 0;
  try {
    number = stoi(current_token_);
  } catch (const std::invalid_argument& e) {
    throw std::runtime_error("Parse Error: " + string(e.what()));
  }
  return number;
}