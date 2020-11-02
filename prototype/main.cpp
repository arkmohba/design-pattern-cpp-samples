#include <iostream>
#include <string>

#include "classes.hpp"

using namespace std;

static const char KEY_STRONG[] = "strong message";
static const char KEY_WARNING[] = "warning box";
static const char KEY_SLASH[] = "slash box";

int main() {
  // セットアップ
  Manager manager;
  UnderlinePen* upen = new UnderlinePen('~');
  MessageBox* mbox = new MessageBox('*');
  MessageBox* sbox = new MessageBox('/');
  manager.register_proto(KEY_STRONG, upen);
  manager.register_proto(KEY_WARNING, mbox);
  manager.register_proto(KEY_SLASH, sbox);

  // プロトタイプから生成
  Product* p1 = manager.create(KEY_STRONG);
  p1->use("Hello World");
  Product* p2 = manager.create(KEY_WARNING);
  p2->use("Hello World");
  Product* p3 = manager.create(KEY_SLASH);
  p3->use("Hello World");

  delete p1, p2, p3;
  delete upen, mbox, sbox;
  return 0;
}
