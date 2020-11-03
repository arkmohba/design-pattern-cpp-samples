#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "factory.hpp"
#include "list_factory.hpp"

const char FACTORY_LIST[] = "list";
const char FORMAT_TABLE[] = "table";

using namespace std;

void usage() {
  cout << "Usage: main_app list  listでhtmlを作成" << endl;
  cout << "Usage: main_app table   tableでhtmlを作成" << endl;
}

FactoryPtr select_factory(string factory_type) {
  if (factory_type == FACTORY_LIST) {
    return FactoryPtr(new ListFactory());
  } else {
    cout << "please set list or table" << endl;
    return nullptr;
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    usage();
    return 0;
  }

  string output_mode = argv[1];
  FactoryPtr factory = select_factory(output_mode);

  if (!factory) {
    cout << "factory is none" << endl;
  }

  // linkを作成する
  // 本来はunique_ptrを使っているのでプロトタイプと組み合わせて、コピーを作れるようにするべき
  // または、作成後変更がないという前提でソース全体をshared_ptrに変更する手もある。
  // 今回はすべて1度しか使われないので、いったんそのままにする。
  LinkPtr asahi = factory->create_link("朝日新聞", "http://www.asahi.com/");
  LinkPtr yomiuri =
      factory->create_link("読売新聞", "http://www.yomiuri.co.jp/");
  LinkPtr us_yahoo = factory->create_link("Yahoo!", "http://www.yahoo.com/");
  LinkPtr jp_yahoo =
      factory->create_link("Yahoo!Japan", "http://www.yahoo.co.jp/");
  LinkPtr excite = factory->create_link("Excite", "http://www.excite.com/");
  LinkPtr google = factory->create_link("Google", "http://www.google.com/");

  TrayPtr tray_news = factory->create_tray("新聞");
  tray_news->add(move(asahi));
  tray_news->add(move(yomiuri));

  TrayPtr tray_yahoo = factory->create_tray("Yahoo!");
  tray_yahoo->add(move(us_yahoo));
  tray_yahoo->add(move(jp_yahoo));

  TrayPtr tray_search = factory->create_tray("サーチエンジン");
  tray_search->add(move(tray_yahoo));
  tray_search->add(move(excite));
  tray_search->add(move(google));

  PagePtr page = factory->create_page("LinkPage", "NoBody");
  page->add(move(tray_news));
  page->add(move(tray_search));
  page->output();
}
