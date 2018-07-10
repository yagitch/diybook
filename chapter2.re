= スマートホームを作る：基本編

まずは最小構成となるシステムを作っていきましょう。手順通りに進めば、このような構成のシステムが出来上がります。

（画像：システム論理構成図）

「アレクサ、ライトをオンにして」→ライトが付く
「アレクサ、ライトをオフにして」→ライトが消える

コピペできるよう、スクリプトはGitHubにも公開しています。
https://github.com/yagitch/

我が家は1Kのひとり暮らしなのでリビングと寝室が一体化しており、これで賄えています。別々でお持ちの方はまずリビングの照明で作ってみましょう。

== 用意するもの

Raspberry Pi（画像）
家庭内LANに有線または無線で接続できること
ネットワーク接続できて常時起動できるならPCや他のシングルボードコンピュータでも可

Amazon Echo dot（画像）
上位機種でも可。

Philips Hue（画像）
ホワイトグラデーションスターターキットが安くておすすめ。Hue Bridgeは旧バージョン（初代）のでも可

== Node-REDを起動する

Raspberry Piの標準OSの1つであるRaspbianにはNode-REDが入っています（2016年11月リリース版以降）。もしGUIが使える場合はNode-REDアイコンから起動して、ブラウザから「http://localhost:1880/」でアクセス可能になります。あるいは、ヘッドレス環境でコンソールのみ使える場合は「node-red-start」コマンドで起動するか、systemctlで自動起動を有効にすればネットワーク内の他ノードのブラウザから1880番ポートにアクセス可能になります。詳しくはNode-RED公式の日本語解説記事をご覧ください。非常にわかりやすいです。

https://nodered.jp/docs/hardware/raspberrypi

Node-REDの操作画面が表示できたら次に進みます。

（画像：操作画面）

== Node-RED Alexa Home Skill Bridgeに登録する

以下のサイトにアクセスし、ユーザ登録します。これはAmazon AlexaからNode-REDに命令を伝えるためのブリッジです。アカウントの登録・維持に費用はかかりません。

https://alexa-node-red.bm.hardill.me.uk/

（画像：ウェブサイトのキャプチャ）

== Node-RED Alexa Home Skill Bridgeでデバイスを追加する

ユーザ登録してから「Devices」画面に移動すると、ブリッジして動かすためのデバイス追加ができます。

（画像：まっさらなDevices画面）

まずは照明を追加してみましょう。「Add device」をクリックすると「Add new device」と書かれた入力画面がポップアップします。

（画像：Add new device画面）

以下のように入力します。

Name: ライト
Description: Hueとシーリングライトを操作します

（画像：入力している画面）

ここで名付けたものが実際にAlexaに呼びかけるスキル名になります。ここでは「ライト」と名付けたので「アレクサ、ライトをオンにして」などと命令することになります。“明かり”や“照明”といった分かりやすい別の単語にしてもかまいません。（もちろん、複数設定を入れて、どのように言っても反応するようにもできます）

入力が完了するとこのような画面になります。

（画像：入力完了画面）

== Amazon AlexaアプリでNode-REDスキルをインストールする

スマートフォンでAmazon Alexaアプリを起動します。まだアプリが入っていなければ、App StoreアプリまたはGoogle Playアプリで「Amazon Alexa」を検索してインストールします。以降、Amazon Echo dotを操作するためにはすべてこのスマートフォンアプリが必要になりますので、Amazon Echo dotの初期セットアップが既に完了しているものとして説明していきます。

Amazon Alexaアプリ起動後、メニューから「スキル」画面に移動し、検索欄から「Node-RED」を探します。
（※本書ではiOS版アプリで説明します。Android版も利用可能です）

（画像：Node-REDスキルの画像）

Node-REDスキルを有効にします。

（画像：Node-REDスキルを有効にしたところの画像）

続いて、「設定」→「スマートホームデバイスの管理」を開きます。

（画像：スマートホーム管理画面）

「デバイスを追加」をタップすると「デバイスを検出しています…」画面が出て、先ほど追加したデバイス「ライト」が検出されます。

（画像：追加された「ライト」画面）

== Hueの設定を確認する

HueのAPIを叩くためにHueのIPアドレスとIDを確認します。
LAN内でブラウザから以下に接続すると、IDとプライベートIPアドレスが返ってきます。

接続先
https://www.meethue.com/api/nupnp

結果
[{"id":"002188fcc8b23d02","internalipaddress":"192.168.0.13"}]

== Node-RED上でAlexaとシェルスクリプトを繋げる

Node-REDの画面上でAlexaと回路をつなげていきます。

（書く：Node-REDの画面操作）

== 実行テスト

Amazon Echo dotに「アレクサ、ライトをオンにして」と話しかけてください。正しく反応すれば「はい」と回答してHueが点きます。
もし「すみません、よく分かりません」などと言われたり、反応音がしつつも何も返してくれない場合は正しく聞き取れていません。私の実感では、いちいち声を張らず小声でボソボソ言っても拾って反応してくれます。
あるいは「ライトが見つかりません」と言われたらスキルがAmazon Echo dotに正しく設定されていません。たとえばひらがなで「らいと」と設定すると認識されません。推測ですが、Amazon Alexaの持っている辞書表記に一字一句合わないと見つからない扱いになるようです。
Hueが点いたのを確認できたら「アレクサ、ライトをオフにして」と話しかけます。Hueの明かりが消えたらこの章のゴールです。これで暗闇の中でもAlexaに話しかけるだけで明かりを付けることができ、手元にHue対応デバイス（純正スイッチやスマートフォンのHueアプリ）がなくても明かりを消すことができます。ひとつ便利になりましたね。

次章では、この最小構成システムを前提に、さらにあなたの家を便利にしていくためのTipsを説明していきます。
