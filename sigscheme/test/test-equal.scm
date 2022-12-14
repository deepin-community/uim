#! /usr/bin/env sscm -C UTF-8
;; -*- buffer-file-coding-system: utf-8 -*-

;;  Filename : test-equal.scm
;;  About    : unit tests for equal?
;;
;;  Copyright (C) 2006 YAMAMOTO Kengo <yamaken AT bp.iij4u.or.jp>
;;  Copyright (c) 2007-2008 SigScheme Project <uim-en AT googlegroups.com>
;;
;;  All rights reserved.
;;
;;  Redistribution and use in source and binary forms, with or without
;;  modification, are permitted provided that the following conditions
;;  are met:
;;
;;  1. Redistributions of source code must retain the above copyright
;;     notice, this list of conditions and the following disclaimer.
;;  2. Redistributions in binary form must reproduce the above copyright
;;     notice, this list of conditions and the following disclaimer in the
;;     documentation and/or other materials provided with the distribution.
;;  3. Neither the name of authors nor the names of its contributors
;;     may be used to endorse or promote products derived from this software
;;     without specific prior written permission.
;;
;;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
;;  IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
;;  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
;;  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
;;  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
;;  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;;  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
;;  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
;;  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
;;  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
;;  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

(require-extension (unittest))

(define tn test-name)
(define case-insensitive-symbol? #f)

(tn "equal? invalid form")
(assert-error  (tn) (lambda () (equal?)))
(assert-error  (tn) (lambda () (equal? #f)))
(assert-error  (tn) (lambda () (equal? #f #f #f)))

(tn "equal? different types")
(assert-eq? (tn) #f (equal? 1 #\1))
(assert-eq? (tn) #f (equal? #\1 "1"))
(assert-eq? (tn) #f (equal? #\1 '("1")))
(assert-eq? (tn) #f (equal? '#("1") '("1")))

(tn "equal? boolean")
(assert-eq? (tn) #t (equal? #f #f))
(assert-eq? (tn) #f (equal? #f #t))
(assert-eq? (tn) #f (equal? #t #f))
(assert-eq? (tn) #t (equal? #t #t))

(tn "equal? null")
(assert-eq? (tn) #t (equal? '() '()))
(if (and (provided? "sigscheme")
         (provided? "siod-bugs"))
    (begin
      (assert-eq? (tn) #t (equal? #f '()))
      (assert-eq? (tn) #t (equal? '() #f)))
    (begin
      (assert-eq? (tn) #f (equal? #f '()))
      (assert-eq? (tn) #f (equal? '() #f))))
(if (symbol-bound? 'vector?)
    (begin
      (assert-eq? (tn) #f (equal? '() '#()))
      (assert-eq? (tn) #f (equal? '#() '()))))

(tn "equal? #<eof>")
(if (provided? "sigscheme")
    (begin
      (assert-eq? (tn) #t (equal? (eof) (eof)))
      (assert-eq? (tn) #f (equal? (eof) (undef)))
      (assert-eq? (tn) #f (equal? (undef) (eof)))
      (assert-eq? (tn) #f (equal? '() (eof)))
      (assert-eq? (tn) #f (equal? (eof) '()))
      (assert-eq? (tn) #f (equal? #f (eof)))
      (assert-eq? (tn) #f (equal? (eof) #f))))

(tn "equal? #<undef>")
(if (provided? "sigscheme")
    (begin
      (assert-eq? (tn) #t (equal? (undef) (undef)))
      (assert-eq? (tn) #f (equal? (eof) (undef)))
      (assert-eq? (tn) #f (equal? (undef) (eof)))
      (assert-eq? (tn) #f (equal? '() (undef)))
      (assert-eq? (tn) #f (equal? (undef) '()))
      (assert-eq? (tn) #f (equal? #f (undef)))
      (assert-eq? (tn) #f (equal? (undef) #f))))

(tn "equal? integer")
(assert-eq? (tn) #t (equal? 0 0))
(assert-eq? (tn) #t (equal? 1 1))
(assert-eq? (tn) #t (equal? 3 3))
(assert-eq? (tn) #t (equal? -1 -1))
(assert-eq? (tn) #t (equal? -3 -3))

(assert-eq? (tn) #f (equal? 0 1))
(assert-eq? (tn) #f (equal? 1 0))
(assert-eq? (tn) #f (equal? 1 3))
(assert-eq? (tn) #f (equal? 3 1))
(assert-eq? (tn) #f (equal? -1 1))
(assert-eq? (tn) #f (equal? 1 -1))
(assert-eq? (tn) #f (equal? -3 3))
(assert-eq? (tn) #f (equal? 3 -3))
(assert-eq? (tn) #f (equal? -1 -3))
(assert-eq? (tn) #f (equal? -3 -1))

(tn "equal? symbol")
(assert-eq? (tn) #t (equal? 'symbol 'symbol))
(assert-eq? (tn) #f (equal? 'symbol1 'symbol2))
(if (and (provided? "sigscheme")
         (provided? "strict-r5rs")
         case-insensitive-symbol?)
    (begin
      (assert-eq? (tn) #t (equal? 'symbol 'SYMBOL))
      (assert-eq? (tn) #t (equal? 'SYMBOL 'symbol))
      (assert-eq? (tn) #t (equal? 'symbol 'Symbol))
      (assert-eq? (tn) #t (equal? 'Symbol 'symbol))
      (assert-eq? (tn) #t (equal? 'symbol 'syMBoL))
      (assert-eq? (tn) #t (equal? 'syMBoL 'symbol)))
    (begin
      (assert-eq? (tn) #f (equal? 'symbol 'SYMBOL))
      (assert-eq? (tn) #f (equal? 'SYMBOL 'symbol))
      (assert-eq? (tn) #f (equal? 'symbol 'Symbol))
      (assert-eq? (tn) #f (equal? 'Symbol 'symbol))
      (assert-eq? (tn) #f (equal? 'symbol 'syMBoL))
      (assert-eq? (tn) #f (equal? 'syMBoL 'symbol))))

(tn "equal? singlebyte char")
(assert-eq? (tn) #t (equal? #\a #\a))
(assert-eq? (tn) #f (equal? #\a #\b))
(assert-eq? (tn) #f (equal? #\b #\a))
(assert-eq? (tn) #t (equal? #\b #\b))

(let ((c1 #\a)
      (c2 #\b))
  (assert-eq? (tn) #t (equal? c1 c1))
  (assert-eq? (tn) #t (equal? c2 c2)))

(tn "equal? multibyte char")
(assert-eq? (tn) #t (equal? #\??? #\???))
(assert-eq? (tn) #f (equal? #\??? #\???))
(assert-eq? (tn) #f (equal? #\??? #\???))
(assert-eq? (tn) #t (equal? #\??? #\???))

(let ((c1 #\???)
      (c2 #\???))
  (assert-eq? (tn) #t (equal? c1 c1))
  (assert-eq? (tn) #t (equal? c2 c2)))

(tn "equal? singlebyte string")
(assert-eq? (tn) #t (equal? "" ""))
(assert-eq? (tn) #t (equal? "a" "a"))
(assert-eq? (tn) #t (equal? "b" "b"))
(assert-eq? (tn) #t (equal? "aBc12!" "aBc12!"))
(let ((s1 "")
      (s2 "a")
      (s3 "b")
      (s4 "aBc12!"))
  (assert-eq? (tn) #t (equal? s1 s1))
  (assert-eq? (tn) #t (equal? s2 s2))
  (assert-eq? (tn) #t (equal? s3 s3))
  (assert-eq? (tn) #t (equal? s4 s4)))
(assert-eq? (tn) #f (equal? "" "a"))
(assert-eq? (tn) #f (equal? "a" ""))
(assert-eq? (tn) #f (equal? "a" "b"))
(assert-eq? (tn) #f (equal? "b" "a"))
(assert-eq? (tn) #f (equal? "a" "A"))
(assert-eq? (tn) #f (equal? "A" "a"))
(assert-eq? (tn) #f (equal? "aBc123!" "aBc12!"))
(assert-eq? (tn) #f (equal? "aBc12!" "aBc123!"))

(tn "equal? multibyte string")
(assert-eq? (tn) #t (equal? "???" "???"))
(assert-eq? (tn) #t (equal? "???" "???"))
(assert-eq? (tn) #t (equal? "???0??????12!" "???0??????12!"))
(let ((s1 "???")
      (s2 "???")
      (s3 "???0??????12!"))
  (assert-eq? (tn) #t (equal? s1 s1))
  (assert-eq? (tn) #t (equal? s2 s2))
  (assert-eq? (tn) #t (equal? s3 s3)))
(assert-eq? (tn) #f (equal? "" "???"))
(assert-eq? (tn) #f (equal? "???" ""))
(assert-eq? (tn) #f (equal? "???" "???"))
(assert-eq? (tn) #f (equal? "???" "???"))
(assert-eq? (tn) #f (equal? "???" "???"))
(assert-eq? (tn) #f (equal? "???" "???"))
(assert-eq? (tn) #f (equal? "???0?????????12!" "???0??????12!"))
(assert-eq? (tn) #f (equal? "???0??????12!" "???0?????????12!"))

(tn "equal? procedure")
(assert-eq? (tn) #t (equal? + +))
(assert-eq? (tn) #f (equal? + -))
(assert-eq? (tn) #f (equal? - +))
(assert-eq? (tn) #t (equal? - -))
(let ((plus +))
  (assert-eq? (tn) #t (equal? + plus))
  (assert-eq? (tn) #t (equal? plus +))
  (assert-eq? (tn) #t (equal? plus plus)))

(tn "equal? syntax")
(assert-error (tn) (lambda () (equal? if if)))
(assert-error (tn) (lambda () (equal? if set!)))
(assert-error (tn) (lambda () (equal? set! if)))
(assert-error (tn) (lambda () (equal? set! set!)))
;; (define syntax if) is an invalid form

(tn "equal? macro")
(if (symbol-bound? 'let-syntax)
    (let-syntax ((macro1 (syntax-rules ()
                           ((_) 'macro1-expanded)))
                 (macro2 (syntax-rules ()
                           ((_) 'macro2-expanded))))
      ;; syntactic keyword as value
      (assert-error (tn) (lambda () (equal? macro1 macro1)))
      (assert-error (tn) (lambda () (equal? macro2 macro1)))
      (assert-error (tn) (lambda () (equal? macro1 macro2)))
      (assert-error (tn) (lambda () (equal? macro2 macro2)))))

(tn "equal? closure")
(let ((closure (lambda () #t)))
  (assert-eq? (tn) #t (equal? closure closure))
  (if (provided? "sigscheme")
      (begin
        (assert-eq? (tn) #f (equal? closure (lambda () #t)))
        (assert-eq? (tn) #f (equal? (lambda () #t) closure))
        (assert-eq? (tn) #f (equal? (lambda () #t) (lambda () #t))))))

(tn "equal? stateful closure")
(let ((stateful (lambda ()
                  (let ((state 0))
                    (lambda ()
                      (set! state (+ state 1))
                      state)))))
  (assert-eq? (tn) #t (equal? stateful stateful))
  (assert-eq? (tn) #f (equal? (stateful) (stateful))))

(let ((may-be-optimized-out (lambda ()
                              (let ((state 0))
                                (lambda ()
                                  (set! state (+ state 1))
                                  0)))))
  (assert-eq? (tn) #t (equal? may-be-optimized-out may-be-optimized-out))
  (if (provided? "sigscheme")
      (assert-eq? (tn) #f (equal? (may-be-optimized-out) (may-be-optimized-out)))))

(letrec ((may-be-unified1 (lambda ()
                            (if (equal? may-be-unified1
                                        may-be-unified2)
                                'optimized-out
                                'not-unified1)))
         (may-be-unified2 (lambda ()
                            (if (equal? may-be-unified1
                                        may-be-unified2)
                                'optimized-out
                                'not-unified2))))
  (if (provided? "sigscheme")
      (begin
        (assert-eq? (tn) #f (equal? may-be-unified1 may-be-unified2))
        (assert-eq? (tn) #f (equal? (may-be-unified1) (may-be-unified2))))
      (begin
        ;; other implementations may pass this
        ;;(assert-eq? (tn) #t (equal? may-be-unified1 may-be-unified2))
        ;;(assert-eq? (tn) #t (equal? (may-be-unified1) (may-be-unified2)))
        )))

(tn "equal? continuation")
(call-with-current-continuation
 (lambda (k1)
   (call-with-current-continuation
    (lambda (k2)
      (assert-eq? (tn) #t (equal? k1 k1))
      (assert-eq? (tn) #f (equal? k1 k2))
      (assert-eq? (tn) #f (equal? k2 k1))
      (assert-eq? (tn) #t (equal? k2 k2))
      (let ((cont k1))
        (assert-eq? (tn) #t (equal? cont cont))
        (assert-eq? (tn) #t (equal? cont k1))
        (assert-eq? (tn) #t (equal? k1 cont))
        (assert-eq? (tn) #f (equal? cont k2))
        (assert-eq? (tn) #f (equal? k2 cont)))))))

(tn "equal? port")
(assert-eq? (tn) #t (equal? (current-output-port) (current-output-port)))
(assert-eq? (tn) #f (equal? (current-input-port) (current-output-port)))
(assert-eq? (tn) #f (equal? (current-output-port) (current-input-port)))
(assert-eq? (tn) #t (equal? (current-input-port) (current-input-port)))
(let ((port (current-input-port)))
  (assert-eq? (tn) #t (equal? port port))
  (assert-eq? (tn) #t (equal? (current-input-port) port))
  (assert-eq? (tn) #t (equal? port (current-input-port)))
  (assert-eq? (tn) #f (equal? (current-output-port) port))
  (assert-eq? (tn) #f (equal? port (current-output-port))))

(tn "equal? pair")
(assert-eq? (tn) #t (equal? '(#t . #t) '(#t . #t)))
(assert-eq? (tn) #t (equal? '(#f . #t) '(#f . #t)))
(assert-eq? (tn) #t (equal? '(#t . #f) '(#t . #f)))
(assert-eq? (tn) #f (equal? '(#f . #t) '(#t . #f)))
(assert-eq? (tn) #t (equal? '(#\a . #\a) '(#\a . #\a)))
(assert-eq? (tn) #t (equal? '(#\a . #\b) '(#\a . #\b)))
(assert-eq? (tn) #t (equal? '(#\b . #\a) '(#\b . #\a)))
(assert-eq? (tn) #f (equal? '(#\a . #\b) '(#\b . #\a)))
(assert-eq? (tn) #t (equal? '("a" . "a") '("a" . "a")))
(assert-eq? (tn) #t (equal? '("a" . "b") '("a" . "b")))
(assert-eq? (tn) #t (equal? '("b" . "a") '("b" . "a")))
(assert-eq? (tn) #f (equal? '("a" . "b") '("b" . "a")))

(assert-eq? (tn) #t (equal? (cons #t #t) (cons #t #t)))
(assert-eq? (tn) #t (equal? (cons #f #t) (cons #f #t)))
(assert-eq? (tn) #t (equal? (cons #t #f) (cons #t #f)))
(assert-eq? (tn) #f (equal? (cons #f #t) (cons #t #f)))
(assert-eq? (tn) #t (equal? (cons #\a #\a) (cons #\a #\a)))
(assert-eq? (tn) #t (equal? (cons #\a #\b) (cons #\a #\b)))
(assert-eq? (tn) #t (equal? (cons #\b #\a) (cons #\b #\a)))
(assert-eq? (tn) #f (equal? (cons #\a #\b) (cons #\b #\a)))
(assert-eq? (tn) #t (equal? (cons "a" "a") (cons "a" "a")))
(assert-eq? (tn) #t (equal? (cons "a" "b") (cons "a" "b")))
(assert-eq? (tn) #t (equal? (cons "b" "a") (cons "b" "a")))
(assert-eq? (tn) #f (equal? (cons "a" "b") (cons "b" "a")))

(tn "equal? list")
(assert-eq? (tn) #t (equal? '(#f) '(#f)))
(assert-eq? (tn) #f (equal? '(#f) '(#t)))
(assert-eq? (tn) #f (equal? '(#t) '(#f)))
(assert-eq? (tn) #t (equal? '(#t) '(#t)))
(assert-eq? (tn) #t (equal? '((#f)) '((#f))))
(assert-eq? (tn) #f (equal? '((#f)) '((#t))))
(assert-eq? (tn) #f (equal? '((#t)) '((#f))))
(assert-eq? (tn) #t (equal? '((#t)) '((#t))))
(assert-eq? (tn) #t (equal? '(1) '(1)))
(assert-eq? (tn) #f (equal? '(1) '(0)))
(assert-eq? (tn) #t (equal? '(1 3 5 0 13)
                            '(1 3 5 0 13)))
(assert-eq? (tn) #f (equal? '(1 3 2 0 13)
                            '(1 3 5 0 13)))
(assert-eq? (tn) #t (equal? '(1 3 (5 0 13))
                            '(1 3 (5 0 13))))
(assert-eq? (tn) #f (equal? '(1 3 (2 0 13))
                            '(1 3 (5 0 13))))
(assert-eq? (tn) #t (equal? '((1)) '((1))))
(assert-eq? (tn) #f (equal? '((1)) '((0))))
(assert-eq? (tn) #t (equal? '((1) (3) (5) (0) (13))
                            '((1) (3) (5) (0) (13))))
(assert-eq? (tn) #f (equal? '((1) (3) (2) (0) (13))
                            '((1) (3) (5) (0) (13))))
(assert-eq? (tn) #t (equal? '(#\a) '(#\a)))
(assert-eq? (tn) #f (equal? '(#\a) '(#\b)))
(assert-eq? (tn) #f (equal? '(#\b) '(#\a)))
(assert-eq? (tn) #t (equal? '((#\a)) '((#\a))))
(assert-eq? (tn) #f (equal? '((#\a)) '((#\b))))
(assert-eq? (tn) #f (equal? '((#\b)) '((#\a))))

(assert-eq? (tn) #t (equal? (list #f) (list #f)))
(assert-eq? (tn) #f (equal? (list #f) (list #t)))
(assert-eq? (tn) #f (equal? (list #t) (list #f)))
(assert-eq? (tn) #t (equal? (list #t) (list #t)))
(assert-eq? (tn) #t (equal? (list (list #f)) (list (list #f))))
(assert-eq? (tn) #f (equal? (list (list #f)) (list (list #t))))
(assert-eq? (tn) #f (equal? (list (list #t)) (list (list #f))))
(assert-eq? (tn) #t (equal? (list (list #t)) (list (list #t))))
(assert-eq? (tn) #t (equal? (list 1) (list 1)))
(assert-eq? (tn) #f (equal? (list 1) (list 0)))
(assert-eq? (tn) #t (equal? (list 1 3 5 0 13)
                            (list 1 3 5 0 13)))
(assert-eq? (tn) #f (equal? (list 1 3 2 0 13)
                            (list 1 3 5 0 13)))
(assert-eq? (tn) #t (equal? (list 1 3 (list 5 0 13))
                            (list 1 3 (list 5 0 13))))
(assert-eq? (tn) #f (equal? (list 1 3 (list 2 0 13))
                            (list 1 3 (list 5 0 13))))
(assert-eq? (tn) #t (equal? (list (list 1)) (list (list 1))))
(assert-eq? (tn) #f (equal? (list (list 1)) (list (list 0))))
(assert-eq? (tn) #t (equal? (list (list 1) (list 3) (list 5) (list 0) (list 13))
                            (list (list 1) (list 3) (list 5) (list 0) (list 13))))
(assert-eq? (tn) #f (equal? (list (list 1) (list 3) (list 2) (list 0) (list 13))
                            (list (list 1) (list 3) (list 5) (list 0) (list 13))))
(assert-eq? (tn) #t (equal? (list #\a) (list #\a)))
(assert-eq? (tn) #f (equal? (list #\a) (list #\b)))
(assert-eq? (tn) #f (equal? (list #\b) (list #\a)))
(assert-eq? (tn) #t (equal? (list (list #\a)) (list (list #\a))))
(assert-eq? (tn) #f (equal? (list (list #\a)) (list (list #\b))))
(assert-eq? (tn) #f (equal? (list (list #\b)) (list (list #\a))))

(assert-eq? (tn) #t (equal? '("") '("")))
(assert-eq? (tn) #t (equal? '(("")) '((""))))
(assert-eq? (tn) #t (equal? '("aBc12!")
                            '("aBc12!")))
(assert-eq? (tn) #t (equal? '("???0??????12!")
                            '("???0??????12!")))
(assert-eq? (tn) #t (equal? '("a" "" "aB1" ("3c" "d") "a")
                            '("a" "" "aB1" ("3c" "d") "a")))
(assert-eq? (tn) #t (equal? '(("aBc12!"))
                            '(("aBc12!"))))
(assert-eq? (tn) #t (equal? '(("???0??????12!"))
                            '(("???0??????12!"))))

(assert-eq? (tn) #t (equal? (list "") (list "")))
(assert-eq? (tn) #t (equal? (list (list "")) (list (list ""))))
(assert-eq? (tn) #t (equal? (list "aBc12!")
                            (list "aBc12!")))
(assert-eq? (tn) #t (equal? (list "???0??????12!")
                            (list "???0??????12!")))
(assert-eq? (tn) #t (equal? (list "a" "" "aB1" (list "3c" "d") "a")
                            (list "a" "" "aB1" (list "3c" "d") "a")))
(assert-eq? (tn) #t (equal? (list (list "aBc12!"))
                            (list (list "aBc12!"))))
(assert-eq? (tn) #t (equal? (list (list "???0??????12!"))
                            (list (list "???0??????12!"))))

(assert-eq? (tn) #f (equal? '("aBc123!")
                            '("aBc12!")))
(assert-eq? (tn) #f (equal? '("???0??????12!")
                            '("???0??????12!")))
(assert-eq? (tn) #f (equal? '("a" "" "aB1" ("3c" "e") "a")
                            '("a" "" "aB1" ("3c" "d") "a")))
(assert-eq? (tn) #f (equal? '(("aBc123!"))
                            '(("aBc12!"))))
(assert-eq? (tn) #f (equal? '(("???0??????12!"))
                            '(("???0??????12!"))))

(assert-eq? (tn) #f (equal? (list "aBc123!")
                            (list "aBc12!")))
(assert-eq? (tn) #f (equal? (list "???0??????12!")
                            (list "???0??????12!")))
(assert-eq? (tn) #f (equal? (list "a" "" "aB1" (list "3c" "e") "a")
                            (list "a" "" "aB1" (list "3c" "d") "a")))
(assert-eq? (tn) #f (equal? (list (list "aBc123!"))
                            (list (list "aBc12!"))))
(assert-eq? (tn) #f (equal? (list (list "???0??????12!"))
                            (list (list "???0??????12!"))))

(assert-eq? (tn) #t
            (equal? '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("L")) #t)))
(assert-eq? (tn) #f
            (equal? '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '(0 #\a "" ("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" #t)))
(assert-eq? (tn) #f
            (equal? '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" #t)
                    '(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)))

(assert-eq? (tn) #t
            (equal? (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (list -1 #\b '("Ls")) #t)
                    (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (list -1 #\b '("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (list -1 #\b '("Ls")) #t)
                    (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (list -1 #\b '("L")) #t)))
(assert-eq? (tn) #f
            (equal? (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (list -1 #\b '("Ls")) #t)
                    (list 0 #\a "" (list "vE" -1 '(#\?))   23 + "aBc" (list -1 #\b '("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (list -1 #\b '("Ls")) #t)
                    (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" #t)))
(assert-eq? (tn) #f
            (equal? (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" #t)
                    (list 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (list -1 #\b '("Ls")) #t)))

(tn "equal? empty vector")
(assert-eq? (tn) #t (equal? '#() '#()))
(assert-eq? (tn) #t (equal? (vector) (vector)))

(let ((v1 '#())
      (v2 (vector)))
  (assert-eq? (tn) #t (equal? v1 v1))
  (assert-eq? (tn) #t (equal? v2 v2))
  (assert-eq? (tn) #t (equal? v1 v2)))

(tn "equal? vector")
(assert-eq? (tn) #t (equal? '#(#f) '#(#f)))
(assert-eq? (tn) #f (equal? '#(#f) '#(#t)))
(assert-eq? (tn) #f (equal? '#(#t) '#(#f)))
(assert-eq? (tn) #t (equal? '#(#t) '#(#t)))
(assert-eq? (tn) #t (equal? '#(#(#f)) '#(#(#f))))
(assert-eq? (tn) #f (equal? '#(#(#f)) '#(#(#t))))
(assert-eq? (tn) #f (equal? '#(#(#t)) '#(#(#f))))
(assert-eq? (tn) #t (equal? '#(#(#t)) '#(#(#t))))
(assert-eq? (tn) #t (equal? '#(1) '#(1)))
(assert-eq? (tn) #f (equal? '#(1) '#(0)))
(assert-eq? (tn) #t (equal? '#(1 3 5 0 13)
                            '#(1 3 5 0 13)))
(assert-eq? (tn) #f (equal? '#(1 3 2 0 13)
                            '#(1 3 5 0 13)))
(assert-eq? (tn) #t (equal? '#(1 3 #(5 0 13))
                            '#(1 3 #(5 0 13))))
(assert-eq? (tn) #f (equal? '#(1 3 #(2 0 13))
                            '#(1 3 #(5 0 13))))
(assert-eq? (tn) #t (equal? '#(#(1)) '#(#(1))))
(assert-eq? (tn) #f (equal? '#(#(1)) '#(#(0))))
(assert-eq? (tn) #t (equal? '#(#(1) #(3) #(5) #(0) #(13))
                            '#(#(1) #(3) #(5) #(0) #(13))))
(assert-eq? (tn) #f (equal? '#(#(1) #(3) #(2) #(0) #(13))
                            '#(#(1) #(3) #(5) #(0) #(13))))
(assert-eq? (tn) #t (equal? '#(#\a) '#(#\a)))
(assert-eq? (tn) #f (equal? '#(#\a) '#(#\b)))
(assert-eq? (tn) #f (equal? '#(#\b) '#(#\a)))
(assert-eq? (tn) #t (equal? '#(#(#\a)) '#(#(#\a))))
(assert-eq? (tn) #f (equal? '#(#(#\a)) '#(#(#\b))))
(assert-eq? (tn) #f (equal? '#(#(#\b)) '#(#(#\a))))

(assert-eq? (tn) #t (equal? (vector #f) (vector #f)))
(assert-eq? (tn) #f (equal? (vector #f) (vector #t)))
(assert-eq? (tn) #f (equal? (vector #t) (vector #f)))
(assert-eq? (tn) #t (equal? (vector #t) (vector #t)))
(assert-eq? (tn) #t (equal? (vector (vector #f)) (vector (vector #f))))
(assert-eq? (tn) #f (equal? (vector (vector #f)) (vector (vector #t))))
(assert-eq? (tn) #f (equal? (vector (vector #t)) (vector (vector #f))))
(assert-eq? (tn) #t (equal? (vector (vector #t)) (vector (vector #t))))
(assert-eq? (tn) #t (equal? (vector 1) (vector 1)))
(assert-eq? (tn) #f (equal? (vector 1) (vector 0)))
(assert-eq? (tn) #t (equal? (vector 1 3 5 0 13)
                            (vector 1 3 5 0 13)))
(assert-eq? (tn) #f (equal? (vector 1 3 2 0 13)
                            (vector 1 3 5 0 13)))
(assert-eq? (tn) #t (equal? (vector 1 3 (vector 5 0 13))
                            (vector 1 3 (vector 5 0 13))))
(assert-eq? (tn) #f (equal? (vector 1 3 (vector 2 0 13))
                            (vector 1 3 (vector 5 0 13))))
(assert-eq? (tn) #t (equal? (vector (vector 1)) (vector (vector 1))))
(assert-eq? (tn) #f (equal? (vector (vector 1)) (vector (vector 0))))
(assert-eq? (tn) #t (equal? (vector (vector 1) (vector 3) (vector 5) (vector 0) (vector 13))
                            (vector (vector 1) (vector 3) (vector 5) (vector 0) (vector 13))))
(assert-eq? (tn) #f (equal? (vector (vector 1) (vector 3) (vector 2) (vector 0) (vector 13))
                            (vector (vector 1) (vector 3) (vector 5) (vector 0) (vector 13))))
(assert-eq? (tn) #t (equal? (vector #\a) (vector #\a)))
(assert-eq? (tn) #f (equal? (vector #\a) (vector #\b)))
(assert-eq? (tn) #f (equal? (vector #\b) (vector #\a)))
(assert-eq? (tn) #t (equal? (vector (vector #\a)) (vector (vector #\a))))
(assert-eq? (tn) #f (equal? (vector (vector #\a)) (vector (vector #\b))))
(assert-eq? (tn) #f (equal? (vector (vector #\b)) (vector (vector #\a))))

(assert-eq? (tn) #t (equal? '#("") '#("")))
(assert-eq? (tn) #t (equal? '#(#("")) '#(#(""))))
(assert-eq? (tn) #t (equal? '#("aBc12!")
                            '#("aBc12!")))
(assert-eq? (tn) #t (equal? '#("???0??????12!")
                            '#("???0??????12!")))
(assert-eq? (tn) #t (equal? '#("a" "" "aB1" #("3c" "d") "a")
                            '#("a" "" "aB1" #("3c" "d") "a")))
(assert-eq? (tn) #t (equal? '#(#("aBc12!"))
                            '#(#("aBc12!"))))
(assert-eq? (tn) #t (equal? '#(#("???0??????12!"))
                            '#(#("???0??????12!"))))

(assert-eq? (tn) #t (equal? (vector "") (vector "")))
(assert-eq? (tn) #t (equal? (vector (vector "")) (vector (vector ""))))
(assert-eq? (tn) #t (equal? (vector "aBc12!")
                            (vector "aBc12!")))
(assert-eq? (tn) #t (equal? (vector "???0??????12!")
                            (vector "???0??????12!")))
(assert-eq? (tn) #t (equal? (vector "a" "" "aB1" (vector "3c" "d") "a")
                            (vector "a" "" "aB1" (vector "3c" "d") "a")))
(assert-eq? (tn) #t (equal? (vector (vector "aBc12!"))
                            (vector (vector "aBc12!"))))
(assert-eq? (tn) #t (equal? (vector (vector "???0??????12!"))
                            (vector (vector "???0??????12!"))))

(assert-eq? (tn) #f (equal? '#("aBc123!")
                            '#("aBc12!")))
(assert-eq? (tn) #f (equal? '#("???0??????12!")
                            '#("???0??????12!")))
(assert-eq? (tn) #f (equal? '#("a" "" "aB1" #("3c" "e") "a")
                            '#("a" "" "aB1" #("3c" "d") "a")))
(assert-eq? (tn) #f (equal? '#(#("aBc123!"))
                            '#(#("aBc12!"))))
(assert-eq? (tn) #f (equal? '#(#("???0??????12!"))
                            '#(#("???0??????12!"))))

(assert-eq? (tn) #f (equal? (vector "aBc123!")
                            (vector "aBc12!")))
(assert-eq? (tn) #f (equal? (vector "???0??????12!")
                            (vector "???0??????12!")))
(assert-eq? (tn) #f (equal? (vector "a" "" "aB1" (vector "3c" "e") "a")
                            (vector "a" "" "aB1" (vector "3c" "d") "a")))
(assert-eq? (tn) #f (equal? (vector (vector "aBc123!"))
                            (vector (vector "aBc12!"))))
(assert-eq? (tn) #f (equal? (vector (vector "???0??????12!"))
                            (vector (vector "???0??????12!"))))

(assert-eq? (tn) #t
            (equal? '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("L")) #t)))
(assert-eq? (tn) #f
            (equal? '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '#(0 #\a "" ("vE" -1 (#\?))  23 + "aBc" (-1 #\b ("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)
                    '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" #t)))
(assert-eq? (tn) #f
            (equal? '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" #t)
                    '#(0 #\a "" #("vE" -1 (#\?)) 23 + "aBc" (-1 #\b ("Ls")) #t)))

(assert-eq? (tn) #t
            (equal? (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (vector -1 #\b '("Ls")) #t)
                    (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (vector -1 #\b '("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (vector -1 #\b '("Ls")) #t)
                    (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (vector -1 #\b '("L")) #t)))
(assert-eq? (tn) #f
            (equal? (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (vector -1 #\b '("Ls")) #t)
                    (vector 0 #\a "" (list "vE" -1 '(#\?))   23 + "aBc" (vector -1 #\b '("Ls")) #t)))
(assert-eq? (tn) #f
            (equal? (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (vector -1 #\b '("Ls")) #t)
                    (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" #t)))
(assert-eq? (tn) #f
            (equal? (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" #t)
                    (vector 0 #\a "" (vector "vE" -1 '(#\?)) 23 + "aBc" (vector -1 #\b '("Ls")) #t)))


(total-report)
