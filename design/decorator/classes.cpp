#include "classes.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string FullBorder::make_line(char ch, int count) {
  stringstream ss;
  for (int i = 0; i < count; i++) {
    ss << ch;
  }
  return ss.str();
}

string FullBorder::get_row_text(int row) {
  if (row == 0)  {
    return "+" + make_line('-', display->get_columns()) + "+";
  } else if (row  == display->get_rows() + 1) {
    return "+" + make_line('-', display->get_columns()) + "+";
  } else {
    return "|" + display->get_row_text(row-1) + "|";
  }
}
