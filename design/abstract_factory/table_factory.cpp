#include "Table_factory.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string TableTray::make_html() {
  ostringstream buffer;
  buffer << "<td>" << endl;
  buffer << caption << endl;
  buffer << "<table width=\"100\" border=\"1\"><tr>" << endl;
  buffer << "<td bgcolor=\"#cccccc\" align=\"center\" colspan=\""
         << items_in_tray.size() << "\"><b>" << caption << "</b></td>";
  buffer << "</tr>" << endl;
  buffer << "<tr>" << endl;
  // tray内のアイテムをリストとして出力
  // unique_ptrなのでコピーでなく参照を受け取らないとエラーになる
  // constで良いのでconst呼び出し。
  for (auto const& item : items_in_tray) {
    buffer << item->make_html();
  }
  buffer << "</tr></table>" << endl;
  buffer << "</td>" << endl;
  return buffer.str();
}

string TablePage::make_html() {
  ostringstream buffer;
  buffer << "<html>";
  buffer << "<header><title>" << title << "</title></head>" << endl;
  buffer << "<body>" << endl;
  buffer << "<table width=\"80%\" border=\"3\">" << endl;
  for (auto const& item : contents) {
    buffer << item->make_html();
  }
  buffer << "</table>" << endl;
  buffer << "<hr><address>" << author << "</address>";
  buffer << "</body>" << endl;
  buffer << "</html>" << endl;
  return buffer.str();
}

LinkPtr TableFactory::create_link(string caption, string url) {
  return make_unique<TableLink>(caption, url);
}

TrayPtr TableFactory::create_tray(string caption) {
  return make_unique<TableTray>(caption);
}

PagePtr TableFactory::create_page(string title, string author) {
  return make_unique<TablePage>(title, author);
}
