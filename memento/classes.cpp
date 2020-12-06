#include "classes.hpp"

#include <unistd.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> Gamer::fruitsname;

Gamer::Gamer(int money_) : money(money_) {
  Gamer::fruitsname.push_back("リンゴ");
  Gamer::fruitsname.push_back("ぶどう");
  Gamer::fruitsname.push_back("バナナ");
  Gamer::fruitsname.push_back("みかん");
}

string Gamer::get_fruit() {
  string prefix = "";
  if (random.get_val(0, 1)) {
    prefix = "おいしい";
  }
  return prefix +
         Gamer::fruitsname[random.get_val(0, Gamer::fruitsname.size() - 1)];
}

void Gamer::bet() {
  int dice = random.get_val(1, 6);
  cout << "dice:" << dice << endl;
  if (dice == 1) {
    money += 100;
    cout << "所持金が増えました。" << endl;
  } else if (dice == 2) {
    money /= 2;
    cout << "所持金が半分になりました。" << endl;
  } else if (dice == 6) {
    string f = get_fruit();
    cout << "フルーツ（" << f << "）をもらいました。" << endl;
    fruits.push_back(f);
  } else {
    cout << "何も起こりませんでした。" << endl;
  }
}

MementoPtr Gamer::create_memento() {
  auto m = shared_ptr<Memento>(new Memento(money));
  for (string fruit : fruits) {
    if (fruit.find("おいしい") != std::string::npos) {
      // フルーツは美味しいものだけ保存
      m->add_fruit(fruit);
    }
  }
  return m;
}

void Gamer::restore_memento(weak_ptr<Memento> w_mement) {
  auto m = w_mement.lock();
  money = m->money;
  fruits = m->get_fruits();
}

string Gamer::to_string() {
  stringstream ss;
  ss << "[money = " << money << ", fruits = [";
  for (int i = 0; i < fruits.size(); i++) {
    if (i > 0) {
      ss << ", ";
    }
    ss << fruits[i];
  }
  ss << "]]";
  return ss.str();
}
