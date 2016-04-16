;; window minimize test

(use msconalloc)

(alloc-and-hide-console SW_MINIMIZE)

(display #\cr)(flush) ; for setup standard ports of gosh-noconsole
(sys-system "date /t")
(sys-system "time /t")
(print "HIT ENTER KEY!")
(flush)
(read-line)

