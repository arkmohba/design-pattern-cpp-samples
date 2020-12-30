#pragma once
#include <string>
#include <vector>

#include "factory.hpp"

// abstract factoryで作る抽象的な部品の1つ
// ページのリンク
class TableLink : public Link {
 public:
  TableLink(std::string caption_, std::string url_) : Link(caption_, url_) {}
  // Itemクラスのインターフェイスを実装
  std::string make_html() {
    return "    <td><a href=\"" + url + "\">" + caption + "</a></td>\n";
  }
};

// abstract factoryで作る抽象的な部品の1つ
// Itemのリスト
class TableTray : public Tray {
 public:
  explicit TableTray(std::string caption): Tray(caption) {}
  // Itemクラスのインターフェイスを実装
  std::string make_html();
};

// abstract factoryで作る製品
// webページ
class TablePage : public Page {
 public:
  TablePage(std::string title_, std::string author_): Page(title_, author_) {}
  // pageのmake_htmlを実装
  std::string make_html();
};

// 抽象クラスの工場クラス
// クラス名からクラスを選択する機能はあまり本質的ではないのでオミットする。
class TableFactory : public Factory {
 public:
  LinkPtr create_link(std::string caption, std::string url);
  TrayPtr create_tray(std::string caption);
  PagePtr create_page(std::string title, std::string author);
};
