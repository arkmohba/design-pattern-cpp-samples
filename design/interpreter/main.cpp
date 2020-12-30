#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"
using namespace std;

int main(int argc, char** argv) {
  ifstream ifs(argv[1]);
  string text;
  while (getline(ifs, text)) {
    cout << "text = \"" << text << "\"" << endl;
    NodePtr node = make_shared<ProgramNode>();
    auto context = make_shared<Context>(text);
    node->parse(context);
    cout << "node = " << node->to_string() << endl;
  }
  ifs.close();
  return 0;
}
