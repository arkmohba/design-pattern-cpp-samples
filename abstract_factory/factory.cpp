#include "factory.hpp"

using namespace std;

void Page::output() {
  string filename = title + ".html";
  ofstream writer(filename);
  writer << make_html();
  writer.close();
  cout << filename << "を作成しました。" << endl;
}
