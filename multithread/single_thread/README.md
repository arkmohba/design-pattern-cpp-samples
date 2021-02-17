# 概要

SingleThreadedExecutionパターンを実装してみたもの。
CriticalSection, Critical Regionとも呼ばれる




# 所感

* C++にはsynchronizedがないのでmutexで代用する。クラスのメソッドであればクラス変数にmutexを持ってもよいが、単純に関数のstatic変数としても良い。（今回はstatic変数）