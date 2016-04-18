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
   また、開発環境に MSYS2/MinGW-w64 (64bit/32bit) を使用する場合には、  
   Gauche の開発最新版のソースの取得、および、コンパイルも必要になります。  
   開発環境のインストールと、Gauche のコンパイルについては、以下のページを参照ください。  
   ＜開発環境に MinGW (32bit) を使う場合＞  
   https://gist.github.com/Hamayama/19d7e779cec0480af0cf  
   ＜開発環境に MSYS2/MinGW-w64 (64bit/32bit) を使う場合＞  
   https://gist.github.com/Hamayama/6666e5d2c8d5167d22f7

2. ファイルのダウンロード  
   本サイト( https://github.com/Hamayama/msconalloc )のソースを、  
   (Download Zip ボタン等で)ダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\msicon の下にファイル一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

3. コンパイルとインストール  
   ＜MinGW (32bit) 環境の場合＞  
   コマンドプロンプトを開いて、以下のコマンドを実行してください。  
   ＜MSYS2/MinGW-w64 (64bit) 環境の場合＞  
   c:\msys64\mingw64_shell.bat を起動して、以下のコマンドの bash 以外を実行してください。  
   ＜MSYS2/MinGW-w64 (32bit) 環境の場合＞  
   c:\msys64\mingw32_shell.bat を起動して、以下のコマンドの bash 以外を実行してください。
   ```
     bash
     cd /c/work/msconalloc
     ./configure    # Makefile等を生成します
     make           # コンパイルを実行します
     make install   # Gaucheのライブラリフォルダにインストールします
     make check     # テストを実行します
   ```
   (注意) コンパイルには、Gauche をコンパイルした開発環境と同じ開発環境を  
   使用してください。例えば、Gauche を MinGW (32bit) 環境でコンパイルして、  
   本モジュールを MSYS2/MinGW-w64 (64bit) 環境でコンパイルすると、  
   エラーが発生して正常に動作しません。  
   
   (注意) 環境によっては make install を実行すると、  
   「*** ERROR: mkstemp failed」というエラーが発生します。  
   このエラーは c:\Program Files (x86) のフォルダに 書き込み権限がないとき等に発生します。  
   その場合は、コマンドプロンプトやバッチファイルを実行するときに、  
   右クリックして、「管理者として実行」を選択してください。  
   そして再度上記のコマンドを実行してください。

- 以上です。


## 使い方
```
  (use msconalloc)          ; モジュールをロードします
  (alloc-and-hide-console)  ; コンソールを割り当てて非表示にします
                            ; (print等を行う前に実行する必要があります)
```

- alloc-and-hide-console は、オプション引数でコマンドプロンプトの画面の表示状態を設定できます。  
  以下の値のいずれかを指定可能です。省略時はSW_HIDEを指定したことになります。
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
  - Windows XP Home SP3
  - Windows 8.1 (64bit)
- 環境
  - MinGW (32bit) (gcc v4.8.1)
  - MSYS2/MinGW-w64 (64bit) (gcc version 5.3.0 (Rev1, Built by MSYS2 project))
  - MSYS2/MinGW-w64 (32bit) (gcc version 5.3.0 (Rev1, Built by MSYS2 project))
- 言語
  - Gauche v0.9.4
  - Gauche v0.9.5_pre1

## 履歴
- 2014-11-26 v1.00 (初版)
- 2014-11-26 v1.01 非表示処理見直し
- 2014-11-27 v1.02 非表示処理修正
- 2014-11-29 v1.03 非表示処理見直し
- 2014-11-30 v1.04 コメント修正のみ
- 2014-12-2  v1.05 Cの関数宣言を修正
- 2016-4-16  v1.06 コメント修正のみ


(2016-4-18)
