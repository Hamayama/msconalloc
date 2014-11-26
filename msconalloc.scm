;; -*- coding: utf-8 -*-
;;
;; msconalloc.scm
;; 2014-11-26 v1.01
;;
;; �����e��
;;   Windows �̃R���\�[���Ȃ��ł� Gauche(gosh-noconsole.exe) �ŁA
;;   �R���\�[���̊��蓖�ĂƔ�\�����s�����߂̃��W���[���ł��B
;;
;;   �Ⴆ�� �R���\�[���Ȃ��ł� Gauche �� print ���ŕW���o�͂ɕ\�����悤�Ƃ���ƁA
;;   Gauche �͎����I�ɃR���\�[�������蓖�Ă�(AllocConsole)�A
;;   �R�}���h�v�����v�g�̉�ʂ�\�����܂��B
;;   �{���W���[�����g���ƁA���̏ꍇ�ɃR�}���h�v�����v�g�̉�ʂ��o���Ȃ��悤��
;;   ���邱�Ƃ��ł��܂��B
;;
;;   �ڍׂɂ��ẮA�ȉ��̃y�[�W���Q�Ƃ��������B
;;   https://github.com/Hamayama/msconalloc
;;
(define-module msconalloc
  (export
    test-msconalloc
    free-console
    alloc-console
    alloc-and-hide-console
    SW_HIDE SW_SHOWNORMAL SW_SHOWMINIMIZED
    SW_MAXIMIZE SW_SHOWMAXIMIZED SW_SHOWNOACTIVATE SW_SHOW
    SW_MINIMIZE SW_SHOWMINNOACTIVE SW_SHOWNA SW_RESTORE
    SW_SHOWDEFAULT SW_FORCEMINIMIZE))
(select-module msconalloc)

;; Loads extension
(dynamic-load "msconalloc")

;;
;; Put your Scheme definitions here
;;

;; ��ʕ\���̒萔
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

