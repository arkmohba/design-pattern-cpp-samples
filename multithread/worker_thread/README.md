# 概要

Worker-Threadパターンを実装してみたもの。

* テーマ1: スレッドを使いまわし、リサイクルしてスループットを上げる。
  * 実際にスループットが上がるかはスレッド起動の重さに依存する。
* テーマ2: キャパシティの制御
  * 実際に同時に処理するリクエスト数より多くワーカーを用意してもメモリの無駄になる。
  * 環境に応じてワーカー数を調整することもできる。
  * メモリ制限があるのでワーカー数似上限はつけること。
  * チャンネルの容量が多ければ、メモリを食うがクライアントとワーカーの処理速度のズレを埋めることができる。（キャパシティとリソースのトレードオフ）
* メソッドの起動（invocation）とメソッドの実行（execution）を分離している。→commandパターンのテーマでもある。
  * 応答性の向上
  * 実行順序の制御
  * キャンセル可能・繰り返し実行可能
  * 分散処理への道
* ワーカーはリクエストのexecute関数の内部は知らなくてよい。→ポリモルフィズム。
  * Requestのサブクラスを作れば具体的な動作はいくらでも変えることができる。

# 所感

* detachをしないと終了時にエラーになるので注意

