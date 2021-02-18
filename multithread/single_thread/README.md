# 概要

SingleThreadedExecutionパターンを実装してみたもの。
CriticalSection, Critical Regionとも呼ばれる

* デッドロックにはならないように注意する。
  * ロックの順序を一意にするなど
* checkメソッドはプライベートで他に呼ばれないのでロックしなくていい。


# 所感

* C++にはsynchronizedがないのでmutexで代用する。クラスのメソッドであればクラス変数にmutexを持ってもよいが、単純に関数のstatic変数としても良い。（今回はstatic変数）
