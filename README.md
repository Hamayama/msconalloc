# msconalloc

## 概要
- Windows のコンソールなし版の Gauche(gosh-noconsole.exe) で、  
  コンソールの割り当てと非表示を行うためのモジュールです。

- 例えば、コンソールなし版の Gauche で、print 等で標準出力に表示を行うと、  
  Gauche は自動的にコンソールを割り当てて(AllocConsole)、コマンドプロンプトの画面を表示します。  
  本モジュールを使うと、このコマンドプロンプトの画面を表示しないようにすることができます。


## インストール方法
1. 事前準備  
   事前にMinGW(32bit)の開発環境がインストールされている必要があります。  
   以下のページを参考にインストールを実施ください。  
   https://gist.github.com/Hamayama/362f2eb14ae26d971ca4

2. ファイルのダウンロード  
   本サイト( https://github.com/Hamayama/msconalloc )のソースを、  
   (Download Zipボタン等で)ダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\msconalloc の下にファイルとフォルダ一式が配置されるように展開してください。

3. コンパイルとインストール  
   コマンドプロンプトを開いて以下を実行してください。
   ```
     bash
     cd /c/work/msconalloc
     ./configure    # Makefile等を生成します
     make           # コンパイルを実行します
     make install   # Gaucheのライブラリフォルダにインストールします
     make check     # テストを実行します
   ```

- 以上です。


## 使い方
```
  (use msconalloc)          ; モジュールをロードします
  (alloc-and-hide-console)  ; コンソールを割り当てて非表示にします
                            ; (print等を行う前に実行する必要があります)
```

- alloc-and-hide-console は、オプション引数でコマンドプロンプトの画面の表示状態を設定できます。  
  以下の引数が指定可能です。省略時はSW_HIDEを指定したことになります。
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
1. Windowsの内部情報を使用しているため、Windowsのバージョンによっては、  
   動作しない可能性があります。

2. alloc-and-hide-console は、他のモジュールが標準入出力にアクセスする前に  
   実行する必要があります。


## 参考情報
- http://nocd5.blog59.fc2.com/?no=410  
  (Process Environment Block -> ProcessParameters という順に取得)

- https://github.com/ckw-mod/ckw-mod  
  (main.cpp の __hide_alloc_console 関数を参考にしました)

- http://stackoverflow.com/questions/6530565/getting-another-process-command-line-in-windows  
  http://stackoverflow.com/questions/18358150/ntqueryinformationprocess-keep-to-fail  
  (NtQueryInformationProcess の使用例等)


## 環境等
  - OS
    - Windows XP Home SP3
    - Windows 8 (64bit)
  - 環境
    - MinGW (32bit) v4.8.1
  - 言語
    - Gauche v0.9.4

## 履歴
- 2014-11-26 v1.00 (初版)


(2014-11-26)
