/*classes header*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

class Singleton {
 private:
  Singleton() { std::cout << "インスタンスを生成しました" << std::endl; }

 public:
  static Singleton* get_instance() {
    // 関数内で生成しないといけない。
    // クラス内の変数として静的に確保することはできなかった。
    // 動的に確保する方法もあるとのこと
    // https://qiita.com/kikuuuty/items/fcf5f7df2f0493c437dc
    static Singleton singleton;
    return &singleton;
  }
};
