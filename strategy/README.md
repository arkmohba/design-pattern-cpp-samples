# 概要

strategyパターンを実装してみたもの。

* 移譲を使ってかんたんに切り替えられるようにしている
  * アルゴリズムを動的に切り替えることもできる
  * 2つのアルゴリズムを使って互いに検算するようなこともできる
* 機能、アルゴリズムをまるごと移譲して切り替えるのがStrategyパターン


# 所感

* 本質的ではないが、Strategyの部分よりHandの実装がSingletonでめんどくさかった。
* Strategy自体もSingletonにして呼び出せる形のほうが良いかもしれない。Statelessにしないと行けないが。そういう意味ではプロトタイプか？