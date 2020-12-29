# 概要

commandパターンを実装してみたもの。

* commandとreceiverに分ける
* commandがreceiverを持つことで複数のreceiverがある場合でも使えるようになる
  * 管理役はcommandとreceiverの対応を気にしなくて良い
* MacroCommandをファイル化すれば現在の状態は保存できる
* 


# 所感

* stack使っているのにイテレータ使っているのはどういうことなのか