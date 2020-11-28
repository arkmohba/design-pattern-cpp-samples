#include "classes.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

void File::accept(VisitorPtr v) { v->visit(this); }

void Directory::accept(VisitorPtr v) { v->visit(this); }

int Directory::get_size() {
  int size = 0;
  for (auto entry : directory) {
    size += entry->get_size();
  }
  return size;
}

EntryPtr Directory::add(EntryPtr entry) {
  directory.push_back(entry);
  return shared_from_this();
}

void ListVisitor::visit(File* file) {
  cout << current_dir << "/" << file->get_name() << " (" << file->get_size()
       << ")" << endl;
}

void ListVisitor::visit(Directory* dir) {
  cout << current_dir << "/" << dir->get_name() << " (" << dir->get_size()
       << ")" << endl;
  // current_dirはvisitorの方で持って調整する。
  auto tmp = current_dir;
  current_dir = current_dir + "/" + dir->get_name();
  for (auto entry : dir->get_entries()) {
    entry->accept(shared_from_this());
  }
  current_dir = tmp;
}
