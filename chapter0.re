= はじめに

本書をお手にとっていただきありがとうございます。

この本はスマートホームを切り口に書いた本ですが、同じようにスマートホームについて書かれた本はとても少ないです。書店に行けば電子工作系の棚に「Raspberry Piで電子工作云々」のような本がずらりと並んでおり、DIYするための断片的なノウハウがたくさん転がっています。しかしながらスマートホームを切り口にして、かつアイデア集のような実例を並べて書いている本はとてもわずかです。

一口に「スマートホーム（あるいはスマートハウス）」と言っても、電機メーカーや住宅機器メーカーが指向する全体最適化された住宅の制御システムから、スマートフォンのアプリと連動した照明機器やお掃除ロボットといったちょっとしたものまで、大小様々な考え方があります。言うなれば全体最適化された大きなシステムは「大きなアプローチ」、電気製品一個から始まるちょっとした自動化は「小さなアプローチ」と言った方が良いかもしれません。

2018年現在の電機メーカーや住宅機器メーカーの提案するライフスタイルは「とりあえず既存商品にセンサーを付けるだけ付けてできることをやろう」という感じのように見られます。それはそれで正しく確実なステップの踏み方だと思います。しかしながらユーザが求めている、よく考えなくても毎日のルーチンは勝手によろしくやってくれるといった究極的なニーズに応えられているかというと、どうもまだ違うような気がします。つまり「大きなアプローチ」にはまだ限界があるということです。

スマートホームがスマート（賢い）であるためには、ユーザのやろうとしている毎日のルーチンを把握して、それを代行したりサポートしたりするものであるべきだと思います。つまりは一つ一つの家庭、ひとりひとりのユーザの求める微妙なニーズをできるだけくみ取るレベルに至らないと「やってほしいことはそうじゃないんだよなぁ」という残念感が漂ってしまうのです。

私は、個々の家電がそういった微妙なニーズをくみ取れるようになるまでには、たとえば人工知能がおおよそ正しく文脈を理解するようになるといった様々なブレイクスルーが必要で、それにはまだまだ（十数年単位の）時間がかかると見ています。

でも、今ふりかえって毎日家で生活していて、今すぐに自動化できそうな部分は多数あります。日が暮れたから手を伸ばしてカーテンを閉めるなんて、よく考えたら人間がやらなくてもよさそうですよね。あるいは、うっかり寝落ちしたら照明くらい勝手に消してほしいですよね。寒い日は何もしなくても朝起きる前に部屋を暖めておいてほしいですよね。

大手通販サイトや家電量販店の売り場を覗くと、そういうことが部分的に解決できそうな商品、つまり小さなアプローチの商品が既にたくさん並んでいます。Hue、WeMo、iRemocon、mornin’などなどです。ただ、そういった小さなアプローチの商品の一つ一つができることには限りがあります。

できれば家のどこかに司令塔があって、多数のセンサーと連動してより賢く動いて欲しいときもあります。たとえば、外気温と室温の差に応じてエアコンの風を強めにしてほしいとか……。

そういった細かいニーズ、DIYで解決しませんか？　たとえばあなたの足下に転がっている古いRaspberry Piなんかを使って。

本書は既に市場に出ている「小さなアプローチ」の商品たちを組み合わせつつ、Raspberry Piのような司令塔を持って複数を連動して動かすことで、なんちゃって「大きなアプローチ」を実現するためのノウハウ・アイデア集です。

大手メーカーが出すお仕着せの商品ではなく、APIを叩いて楽しみながら「なんちゃってスマートホーム」を実現しませんか？　一般的な家庭には不要かもしれないけど我が家には切実にほしい機能を作り上げませんか？

本書はそのガイドとするために書きました。

== 本書が対象とする読者

ざっくり言うと、使っていないRaspberry Piが足下に転がっているようなご家庭を対象にしています。遊べると思って購入して、初めはいじっていたはいいけど、特に活用法も思いつかなくて放置している貴方、ドンピシャの読者です。したがってRaspberry Piの基本的な使い方や、Raspbianをインストールしたりする方法は本書では解説しません。既に動く状態にあるものとして説明していきます。サンプルコードは主にシェルスクリプトと若干Pythonを使っています。コピペでも動くとは思いますが、何かトラブっても自力解決できる力が求められます。とりあえず困ったらググりましょう。

== 本書の内容

本書は、Raspberry Piのようなマイクロボードコンピュータを利用して、さまざまな家電や照明を自動で動かす仕組みをつくるためのガイドです。

「第1章：我が家の例」では実際に動いている我が家の状況を見てもらいます。本書にはあとで様々なスマートホームのレシピが出てきますが、すべて実現させるとこの状態になるというゴールです。

「第2章：スマートホームを作る：基本編」では、まず最小構成となるシステムを作り上げる方法を説明します。本書のタイトルでは“Raspberry PiとHueではじめる”とついていますが、ほかにAmazon Echo dotなども必要になり、本当に一から始める場合は最小構成だけで最大5万円程度が必要になります。

「第3章：スマートホームを作る：応用編」では、第2章で作り上げたシステムに様々な機能を付加していきます。それぞれの機能には依存関係がありますが、説明の順番に作っていけばうまくゴールである「第1章：我が家の例」の状態になるようになっています。

本書でもっとも力を入れたのはこの第3章です。スマートホームを既に自力で作ろうと思っている上級者の方であれば、第3章の目次がもっとも重要な部分となるでしょう。この内容でインスピレーションを感じることがなければ、もう本書でお伝えできることはありません。

それでは、楽しいDIYスマートホームの世界を見ていきましょう。