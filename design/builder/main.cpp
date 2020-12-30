#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "classes.hpp"

static const char FORMAT_PLAIN[] = "plain";
static const char FORMAT_HTML[] = "html";

using namespace std;

void usage() {
  cout << "Usage: main_app plain  プレーンテキストで文書作成" << endl;
  cout << "Usage: main_app html   HTMLファイルで文書作成" << endl;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    usage();
    return 0;
  }

  string output_mode = argv[1];
  if (output_mode == FORMAT_PLAIN) {
    shared_ptr<TextBuilder> text_builder = make_shared<TextBuilder>();
    shared_ptr<Director> director = make_shared<Director>(text_builder);
    director->construct();
    string result = text_builder->getResult();
    cout << result << endl;
  } else if (output_mode == FORMAT_HTML) {
    shared_ptr<HTMLBuilder> html_builder = make_shared<HTMLBuilder>();
    shared_ptr<Director> director = make_shared<Director>(html_builder);
    director->construct();
    string filename = html_builder->getResult();
    cout << filename << "が作成されました。" << endl;
  } else {
    usage();
    return 0;
  }
  return 0;
}
