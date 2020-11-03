#include "classes.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;

Director::Director(BuilderPtr builder_) { builder = builder_; }

void Director::construct() {
  builder->makeTitle("Greating");
  builder->makeString("朝から昼にかけて");
  builder->makeItems(vector<string>{"おはようございます。", "こんにちは。"});
  builder->makeString("夜に");
  builder->makeItems(
      vector<string>{"こんばんは。", "おやすみなさい。", "さようなら。"});
  builder->close();
}

void TextBuilder::makeTitle(string title) {
  buffer.str("");
  buffer << "===========================" << endl;
  buffer << "「" << title << "」" << endl;
  buffer << endl;
}

void TextBuilder::makeString(string s) {
  buffer << "■" << s << endl;
  buffer << endl;
}

void TextBuilder::makeItems(vector<string> strs) {
  for (auto s : strs) {
    buffer << " ・" << s << endl;
  }
  buffer << endl;
}

void TextBuilder::close() {
  buffer << "===========================" << endl;
  buffer << std::flush;
}

void HTMLBuilder::makeTitle(string title) {
  filename = title + ".html";
  ofs.open(filename);
  ofs << "<html>" << endl;
  ofs << "<head><title>" << title << "</title></head>" << endl;
  ofs << "<body>" << endl;
  ofs << "<h1>" << title << "</h1>" << endl;
}

void HTMLBuilder::makeString(string s) { ofs << "<p>" << s << "</p>" << endl; }

void HTMLBuilder::makeItems(vector<string> strs) {
  ofs << "<ul>" << endl;
  for (auto s : strs) {
    ofs << "<li>" << s << "</li>" << endl;
  }
  ofs << "</ul>" << endl;
}

void HTMLBuilder::close() {
  ofs << "</body>" << endl;
  ofs << "</html>" << endl;
  ofs.close();
}
