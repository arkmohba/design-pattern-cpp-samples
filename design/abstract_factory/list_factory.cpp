#include "list_factory.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string ListTray::make_html() {
  ostringstream buffer;
  buffer << "<li>" << endl;
  buffer << caption << endl;
  buffer << "<ul>" << endl;
  // tray内のアイテムをリストとして出力
  // unique_ptrなのでコピーでなく参照を受け取らないとエラーになる
  // constで良いのでconst呼び出し。
  for (auto const& item : items_in_tray) {
    buffer << item->make_html();
  }
  buffer << "</ul>" << endl;
  buffer << "</li>" << endl;
  return buffer.str();
}

string ListPage::make_html() {
  ostringstream buffer;
  buffer << "<html>";
  buffer << "<header><title>" << title << "</title></head>" << endl;
  buffer << "<body>" << endl;
  buffer << "<ul>" << endl;
  for (auto const& item : contents) {
    buffer << item->make_html();
  }
  buffer << "</ul>" << endl;
  buffer << "</body>" << endl;
  buffer << "</html>" << endl;
  return buffer.str();
}

LinkPtr ListFactory::create_link(string caption, string url) {
  return make_unique<ListLink>(caption, url);
}

TrayPtr ListFactory::create_tray(string caption) {
  return make_unique<ListTray>(caption);
}

PagePtr ListFactory::create_page(string title, string author) {
  return make_unique<ListPage>(title, author);
}
