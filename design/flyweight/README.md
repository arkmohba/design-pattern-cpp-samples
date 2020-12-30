# 概要

FlyWeightパターンを実装してみたもの。

* BigCharが共有するもの
* FlyweightFactoryでBigCharを取り出す。
* インスタンスを共有することがテーマ
  * 共有しているものを変更すると複数箇所に影響が及ぶ
  * 同時に反映されるとも言える。
* intrinsicな情報とextrinsicな情報を意識する。
* メモリ生成と消費量が抑えられる。

# 所感

* 