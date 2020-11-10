#pragma once
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

enum HandValue { HAND_VALUE_GUU = 0, HAND_VALUE_CHO = 1, HAND_VALUE_PAA = 2 };

class Hand {
 private:
  static const std::vector<std::string> name_of_hand;
  HandValue hand_value;
  int fight(std::shared_ptr<Hand> h);
  explicit Hand(HandValue hand) : hand_value(hand) {}

 public:
  static const std::vector<std::shared_ptr<Hand>> hands;

  static std::shared_ptr<Hand> get_hand(HandValue hand) { return hands[hand]; }
  bool is_stronger_than(std::shared_ptr<Hand> h) { return fight(h) == 1; }
  bool is_weaker_than(std::shared_ptr<Hand> h) { return fight(h) == 1; }
  std::string to_string() { return name_of_hand[hand_value]; }
};
using HandPtr = std::shared_ptr<Hand>;

class Strategy {
 public:
  virtual HandPtr next_hand() = 0;
  virtual void study(bool win) = 0;
};

class IntRangeRandom {
 private:
  std::mt19937 random_val;

 public:
  IntRangeRandom() : random_val(std::random_device()()) {}
  int get_val(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(random_val);
  }
};

class WinningStrategy : public Strategy {
 private:
  IntRangeRandom random_val;
  bool won = false;
  HandPtr prev_hand;

 public:
  WinningStrategy() {}
  HandPtr next_hand();
  void study(bool win);
};

class ProbStrategy : public Strategy {
 private:
  IntRangeRandom random_val;
  HandValue prev_hand_value;
  HandValue current_hand_value;
  std::unique_ptr<int[][3]> history;
  int get_sum(HandValue hv);

 public:
  ProbStrategy() : history(new int[3][3]) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        history[i][j] = 1;
      }
    }
  }
  HandPtr next_hand();
  void study(bool win);
};

class Player {
 private:
  std::string name;
  std::unique_ptr<Strategy> strategy;
  int win_count = 0;
  int lose_count = 0;
  int game_count = 0;

 public:
  Player(std::string name_, std::unique_ptr<Strategy> strategy_)
      : name(name_), strategy(std::move(strategy_)) {}
  HandPtr next_hand();
  void win();
  void lose();
  void even();
  std::string to_string();
};