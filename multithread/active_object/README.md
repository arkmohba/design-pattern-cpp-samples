# 概要

Active Objectパターンを実装してみたもの。

* Active Objectは外部から受け取った非同期メッセージを自分固有のスレッドで自分の都合が良いタイミングで処理する。
* Producer-Consumer、Thread-Per-Message, Futureパターンを組み合わせる。
* ActiveObjectしかクライアントは見えない。実際に使っているのはProxy。
  * データ取り出しにはFutureパターンを使っているのでメソッドの実行と結果の取得が分離している。
* ProxyはActiveObjectのメソッドをMethodRequestクラスに変換し、Schedulerに渡す。（コマンドパターン？）
* Schedulerは
  * Proxyから渡されたMethodRequestをActivationQueueに投入する。
    * Client役のスレッドで実行
  * ActivationQueueからMethodRquestを取り出して実行する。
    * 自分のスレッドで実行
  * Queueへの投入や取り出しがあるのでここで実行する処理をスケジューリングできる。
* MethodRequestはActiveObjectのメソッドをオブジェクトに対応させており、処理を実際に実行するServantと戻り値を書き込むFutureResultを持ち、メソッドの引数を持つ。
  * 実際のMethodRequestの実装はActiveObjectのメソッドの数だけ実装する必要がある。
* ServantはMethodRequestの実行時に実際に動作するActiveObjectの実装。
* ActivationQueueはMethodRequestをProducer-Consumerパターンでキューする。
  * put_requestはClient、take_requestはSchedulerで実行される。
* パターンの適用の粒度を考えること。小さい粒度ではオーバーヘッドが相対的に大きくなるのでかえって遅くなる可能性がある。
* Proxyはスレッドセーフであり、Servantはスレッドセーフではない。ServantはScheduler内のシングルスレッド内でしか使われない。
* ActiveObjectのメソッドを追加する場合は下記の手順で実行する。
  * ActiveObjectのIFを追加
  * MethodRequestのサブクラスを追加
  * Proxyのメソッドを実装
  * Servantのメソッドを実装
  * 戻り地が必要ならばFutureパターンを使う。FutureObjectはProxyで、RealObjectはServantで作成する。
  * ScheduleThreadの変更は必要ない。そもそもActiveObjectとは直接関係していない。（ProxyはScheduleを使う側、ServantはMethodRequestの中に隠れている。）
* ActiveObject同士で相互に呼び出しを行うこともできる。つまりServant役が更に別のActiveObjectを呼ぶようなシステム。
* メソッド呼び出しのスレッドとメソッド実行のスレッドが違い、間をMethodRequestとResultが行き来する。スレッドを別マシンに分ける事もできる。
* 本質的には重たくてスレッドセーフでないServantの処理とClientの処理のスレッドを分け、スレッド間の非同期通信にProducer-ConsumerパターンとFutureパターンを使い、応答性を上げることが目的。
  * スレッドセーフでないためSchedulerを使ってシングルスレッドでServantを実行する。

# 所感

* 実装するものが多い。
* データの流れ
  * Client→Proxy（FutureResultが返る）→MethodRequest→ActivationQueue→MethodRequest→Servant→RealResult→FutureResult→Client
* スレッドを別マシンに分けるとするとServantの実行結果のRealObjectをFutureObjectに格納するのはどうするのだろうか？（メモリの位置とか。）辞書型のようにしてFutureObjectにIDを振ってキューを通してデータを受け取る？
  * Kafkaとかを使う場合はデータしか行き来しないので、送信、受信の2つのキューを使って送信＆結果格納スレッドと計算処理スレッドに分ける必要がありそう。
  * （それこそプロキシである。）
