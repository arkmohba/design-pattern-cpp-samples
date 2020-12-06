#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <unistd.h>

#include "classes.hpp"

static const int sleep_time_us = 100 * 1000;

using namespace std;

int main() {
  Gamer gamer = Gamer(100);
  MementoPtr memento = gamer.create_memento();
  for (int i = 0; i < 100; i++) {
    cout << "====" << i << endl;
    cout << "現状:" << gamer.to_string() << endl;
    gamer.bet();
    cout << "所持金は" << gamer.get_money() << "円になりました。" << endl;
    if (gamer.get_money() > memento->get_money()) {
      cout << "    （だいぶ増えたので、現在の状態を保存しておこう）" << endl;
      memento = gamer.create_memento();
    } else if (gamer.get_money() < memento->get_money() / 2) {
      cout << "    （だいぶ減ったので、以前の状態に復帰しよう）" << endl;
      gamer.restore_memento(memento);
    }

    usleep(sleep_time_us);
  }
  return 0;
}
