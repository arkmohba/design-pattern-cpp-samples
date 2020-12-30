#include "classes.hpp"

#include <iostream>
#include <string>

using namespace std;

ProductPtr Manager::create(std::string proto_name) {
  return showcase[proto_name]->create_clone();
}

void MessageBox::use(string s) {
  // ヘッダ部分を出力
  size_t s_size = s.size();
  for (auto i = 0; i < s_size + 4; i++) {
    cout << decochar;
  }
  cout << endl;
  // ボディを出力
  cout << decochar << " " << s << " " << decochar << endl;

  // フッターを出力
  for (int i = 0; i < s_size + 4; i++) {
    cout << decochar;
  }
  cout << endl;
}

ProductPtr MessageBox::create_clone() {
  // コピーコンストラクタで複製し、unique_ptrとして返す。
  return ProductPtr(new MessageBox(*this));
}

void UnderlinePen::use(string s) {
  size_t s_size = s.size();
  cout << "\"" << s << "\"" << endl;
  cout << " ";
  for (auto i = 0; i < s_size; i++) {
    cout << ulchar;
  }
  cout << " " << endl;
}

ProductPtr UnderlinePen::create_clone() {
  return ProductPtr(new UnderlinePen(*this));
}
