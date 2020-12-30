
#include "classes.hpp"

#include <iostream>

using namespace std;

void AbstractDisplay::display() {
  int num_iterate = 5;
  open();
  for (int i = 0; i < num_iterate; i++) {
    print();
  }
  close();
}

CharDisplay::CharDisplay(char ch_) : ch(ch_) {}
void CharDisplay::open() { cout << "<<"; }
void CharDisplay::print() { cout << ch; }
void CharDisplay::close() { cout << ">>" << endl; }

StringDisplay::StringDisplay(string target) : str(target) {}
void StringDisplay::open() { cout << line << endl; }
void StringDisplay::print() { cout << "|" <<  str << "|" << endl; }
void StringDisplay::close() { cout << line << endl; }
