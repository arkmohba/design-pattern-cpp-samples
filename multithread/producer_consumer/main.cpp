#include <memory>
#include <thread>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  auto table = make_shared<Table>(3);
  auto cake_id = make_shared<Counter>();
  thread maker_th1(thread_func_maker, table, "MakerThread-1", cake_id);
  thread maker_th2(thread_func_maker, table, "MakerThread-2", cake_id);
  thread maker_th3(thread_func_maker, table, "MakerThread-3", cake_id);
  thread eater_th1(thread_func_eater, table, "EaterThread-1");
  thread eater_th2(thread_func_eater, table, "EaterThread-2");
  thread eater_th3(thread_func_eater, table, "EaterThread-3");

  maker_th1.join();
  maker_th2.join();
  maker_th3.join();
  eater_th1.join();
  eater_th2.join();
  eater_th3.join();
  return 0;
}
