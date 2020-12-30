#include "classes.hpp"

#include <iostream>
#include <string>

using namespace std;

Product* Manager::create(std::string proto_name) {
  Product* p = static_cast<Product*>(showcase[proto_name]);
  return p->create_clone();
}

void MessageBox::use(string s) {
  // ヘッダ部分を出力
  int s_size = s.size();
  for (int i = 0; i < s_size + 4; i++) {
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

Product* MessageBox::create_clone() { return new MessageBox(*this); }

void UnderlinePen::use(string s) {
  int s_size = s.size();
  cout << "\"" << s << "\"" << endl;
  cout << " ";
  for (int i = 0; i < s_size; i++) {
    cout << ulchar;
  }
  cout << " " << endl;
}

Product* UnderlinePen::create_clone() { return new UnderlinePen(*this); }
