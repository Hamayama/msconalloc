;;;
;;; Test msconalloc
;;;

(use gauche.test)

(test-start "msconalloc")
(use msconalloc)
(test-module 'msconalloc)

;; The following is a dummy test code.
;; Replace it for your tests.
(test* "test-msconalloc" "msconalloc is working"
       (test-msconalloc))

;; If you don't want `gosh' to exit with nonzero status even if
;; the test fails, pass #f to :exit-on-failure.
(test-end :exit-on-failure #t)




