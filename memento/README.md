# 概要

Mementoパターンを実装してみたもの。

* Mementoにセーブデータを保存する。
  * 自由に作り、適宜戻れること。
* Mementoはwide interfaceとnarrow interfaceを持つべき
  * wide inferfaceは広域的にOriginatorのデータを持つ。外に露出するべきでない情報も含むAPI
  * narrow interfaceはpublicに出してもいい情報を出すAPI
    * 例えばMementoをmain文の中で保存するならそのAPIをnarrowとして出すべき
    * get_money()は外部に公開しているAPI。Gamerクラスと保存に関して必要な情報はMementoからも見えるようにする必要がある。
    * Mementoはmainから状態を変更することができない。
* Mementoをファイル保存する場合はプログラム更新で読み込めなくなったりするので、賞味期限を考えておくのが良い。
* Originatorを作り込めばよいのでは？
  * CaretakerでMementoを管理したほうが、そのハンドリングの機能を調整する際にOriginatorを変更しなくて良い。
    * Originatorに本来持つべき機能以外のFixを入れなくて良い。


# 所感

* Mementoにセーブデータを保存する感じ
* wide/narrow interfaceとしてC++ではフレンドクラスを利用した。（javaのパッケージの機能が使えないので。）
* Originatorクラスを一通り作ったあとに、保存する内容を決めてMementoを作るのが良さそう
  * フレンドクラスは継承できないので、かんたんに切り替えるのが難しい。
  * テンプレートメソッドを使えばできるかも？
    * でもOriginatorのサブクラスで独自の仕様が入ると、保存する内容も独自になるので、Mementoの内容も変える必要がある。
    * 辞書型で保存してしまう
* OriginatorとMementoはセットで作る感じ。
  * シリアライズして保存するならcerealってライブラリがあるらしい。