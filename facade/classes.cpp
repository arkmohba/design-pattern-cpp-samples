#include "classes.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& input, char delimiter) {
  std::istringstream stream(input);

  std::string field;
  std::vector<std::string> result;
  while (std::getline(stream, field, delimiter)) {
    result.push_back(field);
  }
  return result;
}

void Property::load(string file_path) {
  char sep = '=';
  ifstream fin(file_path);
  string buf;
  while (getline(fin, buf)) {
    auto vals = split(buf, sep);
    auto address = vals[0];
    auto name = vals[1];
    accounts[address] = name;
  }
}

PropertyPtr Database::get_properties(string dbname) {
  string file_path = dbname + ".txt";
  auto prop = make_shared<Property>();
  prop->load(file_path);
  return prop;
}

void HtmlWriter::title(std::string title) {
  auto w = writer.lock();
  (*w) << "<html>"
       << "<head>"
       << "<title>" << title << "</title>"
       << "</head>";
  (*w) << "<body>" << endl;
  (*w) << "<h1>" << title << "</h1>" << endl;
}
void HtmlWriter::paragraph(std::string msg) {
  auto w = writer.lock();
  (*w) << "<p>" << msg << "</p>" << endl;
}
void HtmlWriter::link(std::string href, std::string caption) {
  paragraph("<a href=\"" + href + "\">" + caption + "</a>");
}
void HtmlWriter::mailto(std::string mailaddr, std::string username) {
  link("mailto:" + mailaddr, username);
}

void HtmlWriter::close() {
  auto w = writer.lock();
  (*w) << "</body>"
       << "</html>" << endl;
}

void PageMaker::make_welcome_page(string mailaddr, string output_path) {
  auto mail_prop =
      Database::get_properties("maildata");  // 設定ファイル名は固定
  string user_name = mail_prop->get_properties(mailaddr);
  auto fout = make_shared<ofstream>(output_path);
  auto writer = make_shared<HtmlWriter>(fout);
  writer->title("Welcome to " + user_name + "'s page!");
  writer->paragraph(user_name + "のページへようこそ。");
  writer->paragraph("メールまっていますね。");
  writer->mailto(mailaddr, user_name);
  writer->close();
  fout->close();
  cout << output_path << " is created for " << mailaddr << " (" << user_name
       << ")" << endl;
}