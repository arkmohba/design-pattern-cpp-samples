# 概要

Observerパターンを実装してみたもの。

* SubjectとObserverがかんたんに切り替えられるのがポイント
* 基本的にObserverが呼び出される順序が関係ないようにObserverを実装するべき。
  * ObserverのupdateでSubjectの方を変更する場合は順序が関係してきてしまうので例外的に注意する。
  * 変更と通知が無限ループになる場合はObserverにSubjectから通知されている途中であるというフラグを付けて対処する。
* SubjectからObserverにthisを渡している
  * 実際に使うintを渡してもよいのでは？と考えがちだが、Subjectを複数見ているObserverも考えられる。この場合はSubjectを区別するためにthisを渡す方が良い。（Subjectに処理タイプ名をつけるとか？）
  * SubjectからObserverに情報を渡す場合にあまり限定的な情報を渡すための加工をすると、Observer側の可変性が減る
    * Subjectから渡す情報はシンプルにして、Observer側で意図どおりの加工をするのが良い。


# 所感

* Mediatorパターンは通知者は状態を持たないが、Observerパターンは通知者が状態を持っている。