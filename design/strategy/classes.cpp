#include "classes.hpp"

#include <sstream>
#include <string>
#include <vector>

using namespace std;

const vector<string> Hand::name_of_hand{"グー", "チョキ", "パー"};
const vector<shared_ptr<Hand>> Hand::hands{
    shared_ptr<Hand>(new Hand(HAND_VALUE_GUU)),
    shared_ptr<Hand>(new Hand(HAND_VALUE_CHO)),
    shared_ptr<Hand>(new Hand(HAND_VALUE_PAA))};

int Hand::fight(shared_ptr<Hand> h) {
  if (this == h.get()) {
    return 0;
  } else if ((hand_value + 1) % 3 == h->hand_value) {
    return 1;
  } else {
    return -1;
  }
}

HandPtr WinningStrategy::next_hand() {
  if (!won) {
    prev_hand =
        Hand::get_hand(static_cast<HandValue>(random_val.get_val(0, 2)));
  }
  return prev_hand;
}

void WinningStrategy::study(bool win) { won = win; }

int ProbStrategy::get_sum(HandValue hv) {
  int sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += history[hv][i];
  }
  return sum;
}

HandPtr ProbStrategy::next_hand() {
  int bet = random_val.get_val(0, get_sum(current_hand_value));
  HandValue hand_value = HAND_VALUE_GUU;
  if (bet < history[current_hand_value][0]) {
    hand_value = HAND_VALUE_GUU;
  } else if (bet <
             history[current_hand_value][0] + history[current_hand_value][1]) {
    hand_value = HAND_VALUE_CHO;
  } else {
    hand_value = HAND_VALUE_PAA;
  }
  prev_hand_value = current_hand_value;
  current_hand_value = hand_value;
  return Hand::get_hand(hand_value);
}

void ProbStrategy::study(bool win) {
  if (win) {
    history[prev_hand_value][current_hand_value]++;
  } else {
    history[prev_hand_value][(current_hand_value + 1) % 3]++;
    history[prev_hand_value][(current_hand_value + 2) % 3]++;
  }
}

HandPtr Player::next_hand() { return strategy->next_hand(); }
void Player::win() {
  strategy->study(true);
  win_count++;
  game_count++;
}
void Player::lose() {
  strategy->study(false);
  lose_count++;
  game_count++;
}
void Player::even() { game_count++; }
string Player::to_string() {
  stringstream result;
  result << "[" << name << ":" << game_count << " games, " << win_count
         << " win, " << lose_count << " lose]";
  return result.str();
}