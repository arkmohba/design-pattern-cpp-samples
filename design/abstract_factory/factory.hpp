#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// オブジェクトを共通的に扱うためのスーパークラス
class Item {
 protected:
  std::string caption;
  explicit Item(std::string caption_) : caption(caption_) {}

 public:
  virtual std::string make_html() = 0;
};

using ItemPtr = std::unique_ptr<Item>;

// abstract factoryで作る抽象的な部品の1つ
// ページのリンク
class Link : public Item {
 protected:
  std::string url;

 public:
  Link(std::string caption_, std::string url_) : Item(caption_), url(url_) {}
};

using LinkPtr = std::unique_ptr<Link>;

// abstract factoryで作る抽象的な部品の1つ
// Itemのリスト
class Tray : public Item {
 protected:
  std::vector<ItemPtr> items_in_tray;

 public:
  explicit Tray(std::string caption_) : Item(caption_) {}
  void add(ItemPtr item) { items_in_tray.push_back(std::move(item)); }
};

using TrayPtr = std::unique_ptr<Tray>;

// abstract factoryで作る製品
// webページ
class Page {
 protected:
  std::string title;
  std::string author;
  std::vector<ItemPtr> contents;

 public:
  Page(std::string title_, std::string author_)
      : title(title_), author(author_) {}
  void add(ItemPtr item) { contents.push_back(std::move(item)); }

  // make_html部分はtemplateメソッド
  virtual std::string make_html() = 0;
  void output();
};

using PagePtr = std::unique_ptr<Page>;

// 抽象クラスの工場クラス
// クラス名からクラスを選択する機能はあまり本質的ではないのでオミットする。
class Factory {
 public:
  virtual LinkPtr create_link(std::string caption, std::string url) = 0;
  virtual TrayPtr create_tray(std::string caption) = 0;
  virtual PagePtr create_page(std::string title, std::string author) = 0;
};

using FactoryPtr = std::unique_ptr<Factory>;
