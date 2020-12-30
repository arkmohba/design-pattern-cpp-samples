#include <iostream>
#include <string>
#include <memory>
#include <utility>

#include "classes.hpp"

using namespace std;

static const char KEY_STRONG[] = "strong message";
static const char KEY_WARNING[] = "warning box";
static const char KEY_SLASH[] = "slash box";

int main() {
  // セットアップ
  Manager manager;
  auto upen = make_unique<UnderlinePen>('~');
  auto mbox = make_unique<MessageBox>('*');
  auto sbox = make_unique<MessageBox>('/');
  // ここで所有権をmanagerに渡す。
  // shared_ptrで渡すべき？→オブジェクトが乱立してしまうから古いものが必要だったら新しく生成すべきか？
  manager.register_proto(KEY_STRONG, move(upen));
  manager.register_proto(KEY_WARNING, move(mbox));
  manager.register_proto(KEY_SLASH, move(sbox));

  // プロトタイプから生成
  ProductPtr p1 = manager.create(KEY_STRONG);
  p1->use("Hello World");
  ProductPtr p2 = manager.create(KEY_WARNING);
  p2->use("Hello World");
  ProductPtr p3 = manager.create(KEY_SLASH);
  p3->use("Hello World");

  return 0;
}
