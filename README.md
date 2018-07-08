# msconalloc

## 概要
- Windows のコンソールなし版の Gauche (gosh-noconsole.exe) で、  
  コンソールの割り当てと非表示を行うためのモジュールです。

- 例えば、コンソールなし版の Gauche で、print 等で標準出力に表示を行うと、  
  Gauche は自動的にコンソールを割り当てて (AllocConsole)、コマンドプロンプトの画面を表示します。  
  本モジュールを使うと、このコマンドプロンプトの画面を表示しないようにすることができます。


## インストール方法
1. 事前準備  
   事前に、Gauche および開発環境がインストールされている必要があります。  
   Gauche については、以下のページに Windows用バイナリインストーラ があるので、インストールを実施ください。  
   http://practical-scheme.net/gauche/download-j.html  
   (すでにインストール済みであれば本手順は不要です)  
   
   また、開発環境については、MSYS2/MinGW-w64 (64bit/32bit) の開発環境が必要です。  
   以下のページを参考に インストールを実施ください。  
   https://gist.github.com/Hamayama/eb4b4824ada3ac71beee0c9bb5fa546d  
   (すでにインストール済みであれば本手順は不要です)  
   
   (注意) 32bitと64bitの成果物の混在には注意してください。  
   (例えば、32bit版の Gauche から、64bitのライブラリを呼び出すと、エラーになります)

2. ファイルのダウンロード  
   本サイト ( https://github.com/Hamayama/msconalloc ) のソースを、  
   (Download Zip ボタン等で) ダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\msconalloc の下にファイル一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

3. コンパイルとインストール  
   ＜MSYS2/MinGW-w64 (64bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 64bit Shell を起動して、以下のコマンドを実行してください。  
   ＜MSYS2/MinGW-w64 (32bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 32bit Shell を起動して、以下のコマンドを実行してください。  
   ( c:\work にソースを展開した場合)  
   ```
     cd /c/work/msconalloc
     ./configure   # Makefile等を生成します
     make          # コンパイルを実行します
     make install  # Gaucheのライブラリフォルダにインストールします
     make check    # テストを実行します
   ```
   (注意) 環境によっては make install を実行すると、  
   「*** ERROR: mkstemp failed」というエラーが発生します。  
   このエラーは c:\Program Files (x86) のフォルダに 書き込み権限がないとき等に発生します。  
   その場合には、プログラムメニューからの開発環境の起動時に右クリックして、  
   「管理者として実行」を選択してください。  
   そして再度上記のコマンドを実行してください。

- 以上です。


## 使い方
```
  (use msconalloc)          ; モジュールをロードします
  (alloc-and-hide-console)  ; コンソールを割り当てて非表示にします
                            ; (print等を行う前に実行する必要があります)
```

- alloc-and-hide-console は、オプション引数でコマンドプロンプトの画面の表示状態を設定できます。  
  以下の値のいずれかを指定可能です。省略時は SW_HIDE を指定したことになります。
```
    SW_HIDE             非表示
    SW_SHOWNORMAL       表示+最大最小解除+アクティブ
    SW_SHOWMINIMIZED    最小化+アクティブ
    SW_MAXIMIZE         最大化
    SW_SHOWMAXIMIZED    最大化+アクティブ
    SW_SHOWNOACTIVATE   表示+最大最小解除+非アクティブ
    SW_SHOW             表示+アクティブ
    SW_MINIMIZE         最小化
    SW_SHOWMINNOACTIVE  最小化+非アクティブ
    SW_SHOWNA           表示+非アクティブ
    SW_RESTORE          最大最小解除+アクティブ
    SW_SHOWDEFAULT      起動時に指定された表示
    SW_FORCEMINIMIZE    強制的に最小化(別スレッドのウィンドウに使用)
```


## 注意事項
1. Windows の内部情報を使用しているため、Windows のバージョンによっては、  
   動作しない可能性があります。

2. alloc-and-hide-console は、他のモジュールが標準入出力にアクセスする前に  
   実行する必要があります。


## 参考情報
- http://nocd5.blog59.fc2.com/?no=410  
  (Process Environment Block -> ProcessParameters という順に取得)

- https://github.com/ckw-mod/ckw-mod  
  (main.cpp の `__hide_alloc_console` 関数を参考にしました)

- http://stackoverflow.com/questions/6530565/getting-another-process-command-line-in-windows  
  http://stackoverflow.com/questions/18358150/ntqueryinformationprocess-keep-to-fail  
  (NtQueryInformationProcess の使用例等)


## 環境等
- OS
  - Windows 8.1 (64bit)
  - Windows XP Home SP3
- 環境
  - MSYS2/MinGW-w64 (64bit/32bit) (gcc version 7.3.0 (Rev2, Built by MSYS2 project))
  - MinGW (32bit) (gcc version 6.3.0 (MinGW.org GCC-6.3.0-1))
- 言語
  - Gauche v0.9.6
  - Gauche v0.9.5
  - Gauche v0.9.4

## 履歴
- 2014-11-26 v1.00 (初版)
- 2014-11-26 v1.01 非表示処理見直し
- 2014-11-27 v1.02 非表示処理修正
- 2014-11-29 v1.03 非表示処理見直し
- 2014-11-30 v1.04 コメント修正のみ
- 2014-12-2  v1.05 Cの関数宣言を修正
- 2016-4-16  v1.06 コメント修正のみ
- 2016-10-14 v1.06 README修正のみ(Gauche v0.9.5 で動作確認)
- 2018-7-9   v1.06 README修正のみ(Gauche v0.9.6 で動作確認)


(2018-7-9)
