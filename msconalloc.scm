;; -*- coding: utf-8 -*-
;;
;; msconalloc.scm
;; 2016-4-16 v1.06
;;
;; ＜内容＞
;;   Windows のコンソールなし版の Gauche (gosh-noconsole.exe) で、
;;   コンソールの割り当てと非表示を行うためのモジュールです。
;;
;;   例えば、コンソールなし版の Gauche で、print 等で標準出力に表示を行うと、
;;   Gauche は自動的にコンソールを割り当てて (AllocConsole)、コマンドプロンプトの画面を表示します。
;;   本モジュールを使うと、このコマンドプロンプトの画面を表示しないようにすることができます。
;;
;;   詳細については、以下のページを参照ください。
;;   https://github.com/Hamayama/msconalloc
;;
(define-module msconalloc
  (export
    test-msconalloc
    free-console
    alloc-console
    alloc-and-hide-console
    SW_HIDE           SW_SHOWNORMAL  SW_SHOWMINIMIZED SW_MAXIMIZE        SW_SHOWMAXIMIZED
    SW_SHOWNOACTIVATE SW_SHOW        SW_MINIMIZE      SW_SHOWMINNOACTIVE SW_SHOWNA
    SW_RESTORE        SW_SHOWDEFAULT SW_FORCEMINIMIZE))
(select-module msconalloc)

;; Loads extension
(dynamic-load "msconalloc")

;;
;; Put your Scheme definitions here
;;

;; 画面表示の定数
(define SW_HIDE             0)
(define SW_SHOWNORMAL       1)
(define SW_SHOWMINIMIZED    2)
(define SW_MAXIMIZE         3)
(define SW_SHOWMAXIMIZED    3)
(define SW_SHOWNOACTIVATE   4)
(define SW_SHOW             5)
(define SW_MINIMIZE         6)
(define SW_SHOWMINNOACTIVE  7)
(define SW_SHOWNA           8)
(define SW_RESTORE          9)
(define SW_SHOWDEFAULT     10)
(define SW_FORCEMINIMIZE   11)

