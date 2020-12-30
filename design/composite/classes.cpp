#include "classes.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Directory::print_list(string prefix) {
  cout << prefix << "/" << to_string() << endl;
  for (auto entry : directory) {
    entry->print_list(prefix + "/" + name);
  }
}

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
