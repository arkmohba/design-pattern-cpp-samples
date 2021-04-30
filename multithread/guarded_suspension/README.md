# 概要

Guard Suspensionパターンを実装してみたもの。

* 今回使ったキュー自体はスレッドセーフではない。
* ガード条件が成立するまでwhileで待つ。
  * waitしてポーリングの負荷を減らす。
  * waitはnotify_one, notify_allで通知が来る。
  * notify_xxxはガード条件を成立させることができるスレッドが、条件成立後実行する。
* synchronizedは下記2つのアクションがまとめて必ず1つのスレッドから実行されることを保証している。これはsingle threaded executionパターンである。
  * 要素が存在するかのチェック
  * 要素を一個取り出す。
* guarded_suspensionはマルチスレッド版のifのようなもの。
* wait後、ガード条件が成立していなければまたwaitに入る。タイムアウトで処理を変えるなどを行う。→Balkingパターンの補講。
* wait/notifyはRequestQueueの中に閉じる。再利用性が高い。


# 所感

* C++での実装ではcondition_variableを使ったwaitにて実装した。やっていることは変わらない。
* JavaだとスレッドセーフなQueueがあるが、C++だと標準ライブラリにはない。boostやtbbなどが使える。
