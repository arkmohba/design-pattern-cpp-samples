#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  auto strat1 = make_unique<WinningStrategy>();
  Player player1 = Player("Taro", move(strat1));
  auto start2 = make_unique<ProbStrategy>();
  Player player2 = Player("Hana", move(start2));

  for (int i = 0; i < 10000; i++) {
    HandPtr next_hand1 = player1.next_hand();
    HandPtr next_hand2 = player2.next_hand();
    if (next_hand1->is_stronger_than(next_hand2)) {
      cout << "Winner: " << player1.to_string() << endl;
      player1.win();
      player2.lose();
    } else if (next_hand2->is_stronger_than(next_hand1)) {
      cout << "Winner: " << player2.to_string() << endl;
      player1.lose();
      player2.win();
    } else {
      cout << "Even..." << endl;
      player1.even();
      player2.even();
    }
  }
  cout << "Total result:" << endl;
  cout << player1.to_string() << endl;
  cout << player2.to_string() << endl;
  return 0;
}
