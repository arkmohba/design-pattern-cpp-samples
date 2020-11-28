#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

using namespace std;

int main() {
  cout << "Making root entries" << endl;
  EntryPtr root_dir = make_shared<Directory>("root");
  EntryPtr bin_dir = make_shared<Directory>("bin");
  EntryPtr tmp_dir = make_shared<Directory>("tmp");
  EntryPtr usr_dir = make_shared<Directory>("usr");
  root_dir->add(bin_dir);
  root_dir->add(tmp_dir);
  root_dir->add(usr_dir);
  bin_dir->add(make_shared<File>("vi", 10000));
  bin_dir->add(make_shared<File>("latex", 20000));
  root_dir->accept(make_shared<ListVisitor>());

  cout << endl;
  cout << "Making user entries..." << endl;
  EntryPtr yuki = make_shared<Directory>("yuki");
  EntryPtr hanako = make_shared<Directory>("hanako");
  EntryPtr tomura = make_shared<Directory>("tomura");
  usr_dir->add(yuki)->add(hanako)->add(tomura);

  yuki->add(make_shared<File>("diary.html", 100))
      ->add(make_shared<File>("Composite.java", 200));
  hanako->add(make_shared<File>("memo.tex", 300));
  tomura->add(make_shared<File>("game.doc", 400))
      ->add(make_shared<File>("junk.mail", 500));
  root_dir->accept(make_shared<ListVisitor>());
  return 0;
}
