# 概要

Producer-Consumerパターンを実装してみたもの。

* 生産者(producer)が消費者(Consumer)に安全にデータを渡す。
  * 処理速度のズレを吸収する
  * データが生産されていないケースに対応
  * 送り先がデータを受け取る状態ではないケースに対応
* 一般には複数のProducer, Consumerを想定するが、単数同士の場合をPipeパターンと呼ぶ。
* put, takeではguarded suspensionを使う（排他制御）。かつwaitでguarded suspensionを行う。中継点となるデータをチャネルと呼ぶ。
* waitやnotifyはTableクラス内に閉じているので使う方は、マルチスレッドであることを気にしなくて良い。
* チャネルへの連絡だけロックが掛かるが、それ以外は各スレッドが各々作業を進めて待ちが発生しないのが利点。
* チャネルが受け取ったデータをどの順で渡すかについて
  * FIFOQueueとして渡す。（今回実装したもの）
  * スタックとして渡す。（プログラムではあまり見かけないが、現実世界ではよくある。）
  * より一般には優先順位付きキュー
* 単数Consumerの場合、取り出しの排他制御が不必要になる。その分、パフォーマンスを上げることができる場合がある。（JavaのSwingなど）


# 所感

* わざわざ配列を使っているのはメモリ確保とかのコスト削減のため？
  * 上限がないものを作ってもいいが、いずれはメモリオーバーフローするので、究極的には同じこと。