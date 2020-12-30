# 概要

interpreterパターンを実装してみたもの。

* PrimitiveCommandが再帰の終わりを担当する
* ContextはNodeとは別で用意する。
* 正規表現もミニ言語
* バッチ処理言語もInterpreterパターンで処理できる
* トークンを１個多く読みすぎたり、読み残したりするバグが多い。どこまでトークンを読んでいるかを意識するべし。
* ミニ言語はBNFと決定木を使って作る。それを解釈してInterpreterパターンを実装する。


# 所感

* CommandとRepeatCommandが別クラスになるのはぱっと見気づかなそう。BNFをベースにすると当たり前だが。