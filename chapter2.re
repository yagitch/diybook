= スマートホームを作る：基本編

まずは最小構成となるシステムを作っていきましょう。手順通りに進めば、このような構成のシステムが出来上がります。

//image[2-0-1][論理構成図(仮)][scale=0.8]

「アレクサ、ライトをオンにして」→Hueの明かりが点く@<br>{}
「アレクサ、ライトをオフにして」→Hueが明かりが消える

本書で使用しているスクリプトは GitHub にも公開しています。
@<href>{https://github.com/yagitch/auto/}

我が家は 1K のひとり暮らしなのでリビングと寝室の区別がありませんが、別々でお持ちの方はまずリビングの照明で作ってみましょう。

== 用意するもの

//indepimage[2-1-1]

: Raspberry Pi
  家庭内 LAN に有線または無線で接続できること。どのバージョンでも OK です。ネットワーク接続できて常時起動できるなら PC や他のシングルボードコンピュータでも可。

//indepimage[2-1-2]

: Amazon Alexa デバイス
  我が家ではAmazon Echo dot を使用しています。Amazon Alexaが使えればサードパーティ製または上位機種でも可。初期セットアップができているものとして以降説明します。

//indepimage[2-1-3]

: Philips Hue
  ホワイトグラデーションスターターキットが安くておすすめ。Hue Bridge は旧バージョン（初代）のでも可。初期セットアップができているものとして以降説明します。

== Node-RED を起動する

Raspberry Pi の標準 OS の1つである Raspbian には Node-RED が入っています（2016年11月リリース版以降）。もし GUI が使える場合は Node-RED アイコンから起動して、ブラウザから http://localhost:1880/ でアクセス可能になります。あるいは、ヘッドレス環境でコンソールのみ使える場合は node-red-start コマンドで起動するか、systemctl で自動起動を有効にすれば LAN 内の他ノードのブラウザから1880番ポートにアクセス可能になります。詳しくは Node-RED 公式の解説記事をご覧ください。とても分かりやすいです。

@<href>{https://nodered.jp/docs/hardware/raspberrypi}

Node-RED の初期画面(@<img>{2-2-1})が表示できたら次に進みます。

//image[2-2-1][Node-RED の初期画面]

== Node-RED Alexa Home Skill Bridge に登録する

以下のサイトにアクセスし、ユーザ登録します。これは Amazon Alexa から Node-RED に命令を伝えるためのブリッジです。アカウントの登録・維持に費用はかかりません。

@<href>{https://alexa-node-red.bm.hardill.me.uk/}

//image[2-3-1][Node-RED Alexa Home Skill Bridge のトップページ][scale=0.8]

#@# FIXME: 画像にブラウザの枠を入れること、表示崩れを改善すること

== Node-RED Alexa Home Skill Bridge でデバイスを追加する

ユーザ登録してから「 Devices 」画面に移動すると、ブリッジして動かすためのデバイス追加ができます。

（画像：まっさらな Devices 画面）

まずは照明を追加してみましょう。「 Add device 」をクリックすると「 Add new device 」と書かれた入力画面がポップアップします。

（画像： Add new device 画面）

以下のように入力します。

Name: ライト@<br>{}
Description: Hue とシーリングライトを操作します

（画像：入力している画面）

ここで名付けたものが実際に Amazon Alexa に呼びかけるスキル名になります。ここでは「ライト」と名付けたので「アレクサ、ライトをオンにして」などと命令することになります。“明かり”や“照明”といった分かりやすい別の単語にしてもかまいません。（もちろん、複数設定を入れて、どのように言っても反応するようにもできます）

入力が完了するとこのような画面になります。

（画像：入力完了画面）

== Amazon Alexa アプリで Node-RED スキルをインストールする

スマートフォンで Amazon Alexa アプリを起動します。まだアプリが入っていなければ、App Store アプリまたは Google Play アプリで「 Amazon Alexa 」を検索してインストールします。以降、Amazon Echo dot を操作するためにはすべてこのスマートフォンアプリが必要になりますので、Amazon Echo dot の初期セットアップが既に完了しているものとして説明していきます。

Amazon Alexa アプリ起動後、メニューから「スキル」画面に移動し、検索欄から「 Node-RED 」を探します。
（※本書では iOS 版アプリで説明します。Android 版も利用可能です）

（画像： Node-RED スキルの画像）

Node-RED スキルを有効にします。

（画像：Node-REDスキルを有効にしたところの画像）

続いて、「設定」→「スマートホームデバイスの管理」を開きます。

（画像：スマートホーム管理画面）

「デバイスを追加」をタップすると「デバイスを検出しています…」画面が出て、先ほど追加したデバイス「ライト」が検出されます。

（画像：追加された「ライト」画面）

== Hue の設定を確認する

Hue の API を叩くために Hue の IP アドレスと ID を確認します。
LAN 内でブラウザから以下に接続すると、ID とプライベート IP アドレスが返ってきます。

接続先
https://www.meethue.com/api/nupnp

結果
[{"id":"002188fcc8b23d02","internalipaddress":"192.168.0.13"}]

（画像：ブラウザの画面）

== Node-RED 上で Amazon Alexa とスクリプトを繋げる

Node-RED の画面上で Amazon Alexa と回路をつなげていきます。

（書く： Node-RED の画面操作）

== 実行テスト

Amazon Alexa デバイスに「アレクサ、ライトをオンにして」と話しかけてください。正しく反応すれば「はい」と回答して Hue が点きます。

もし「すみません、よく分かりません」などと言われたり、反応音がしつつも何も返してくれない場合は正しく聞き取れていません。私の実感では、いちいち声を張らず小声でボソボソ言っても拾って反応してくれます。

あるいは「ライトが見つかりません」と言われたらスキルが Amazon Alexa デバイスに正しく設定されていません。たとえばひらがなで「らいと」と設定すると認識されません。推測ですが、Amazon Alexa の持っている辞書表記に一字一句合わないと見つからない扱いになるのではないかと思います。

Hue が点いたのを確認できたら「アレクサ、ライトをオフにして」と話しかけます。Hue の明かりが消えたらこの章のゴールです。これで暗闇の中でも Amazon Alexa に話しかけるだけで明かりを付けることができ、手元に Hue 対応デバイス（純正スイッチやスマートフォンの Hue アプリ）がなくても明かりを消すことができます。ひとつ便利になりましたね。

第3章では、この最小構成システムを前提に、さらにあなたの家を便利にしていくための Tips を説明していきます。
