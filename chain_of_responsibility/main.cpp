#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  shared_ptr<Support> alice = make_shared<NoSupport>("Alice");
  shared_ptr<Support> bob = make_shared<LimitSupport>("Bob", 100);
  shared_ptr<Support> charlie = make_shared<SpecialSupport>("Charlie", 429);
  shared_ptr<Support> diana = make_shared<LimitSupport>("Diana", 200);
  shared_ptr<Support> elmo = make_shared<OddSupport>("Elmo");
  shared_ptr<Support> fred = make_shared<LimitSupport>("Fred", 300);
  // 連鎖の形成
  alice->set_next(bob)
      .lock()
      ->set_next(charlie)
      .lock()
      ->set_next(diana)
      .lock()
      ->set_next(elmo)
      .lock()
      ->set_next(fred);

  for (int i = 0; i < 500; i+=33) {
    alice->support(make_shared<Trouble>(i));
  }
  return 0;
}
