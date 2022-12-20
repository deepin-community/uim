;;  Filename : test-letrec.scm
;;  About    : unit test for R5RS letrec
;;
;;  Copyright (C) 2005-2006 YAMAMOTO Kengo <yamaken AT bp.iij4u.or.jp>
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

(define *test-track-progress* #f)
(define tn test-name)


;;
;; letrec
;;
(tn "letrec invalid form")
;; bindings and body required
(assert-error  (tn) (lambda ()
                      (letrec)))
(assert-error  (tn) (lambda ()
                      (letrec ())))
(assert-error  (tn) (lambda ()
                      (letrec ((a)))))
(assert-error  (tn) (lambda ()
                      (letrec ((a 1)))))
(assert-error  (tn) (lambda ()
                      (letrec (a 1))))
(assert-error  (tn) (lambda ()
                      (letrec a)))
(assert-error  (tn) (lambda ()
                      (letrec #())))
(assert-error  (tn) (lambda ()
                      (letrec #f)))
(assert-error  (tn) (lambda ()
                      (letrec #t)))
;; bindings must be a list
(assert-error  (tn) (lambda ()
                      (letrec a 'val)))
(if (provided? "siod-bugs")
    (assert-equal? (tn)
                   'val
                   (letrec #f 'val))
    (assert-error  (tn) (lambda ()
                          (letrec #f 'val))))
(assert-error  (tn) (lambda ()
                      (letrec #() 'val)))
(assert-error  (tn) (lambda ()
                      (letrec #t 'val)))
;; each binding must be a 2-elem list
(assert-error  (tn) (lambda ()
                      (letrec (a 1) 'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((a)) 'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((a 1 'excessive)) 'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((a 1) . (b 2)) 'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((a . 1)) 'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((a  1)) . a)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((a  1)) 'val . a)))
(assert-error  (tn)
               (lambda ()
                 (letrec (1) #t)))

(tn "letrec binding syntactic keyword")
(assert-equal? (tn) 7 (letrec ((else 7)) else))
(assert-equal? (tn) 8 (letrec ((=> 8)) =>))
(assert-equal? (tn) 9 (letrec ((unquote 9)) unquote))
(assert-error  (tn) (lambda () else))
(assert-error  (tn) (lambda () =>))
(assert-error  (tn) (lambda () unquote))

(tn "letrec env isolation")
;; referencing a variable within bindings evaluation is invalid
(assert-error  (tn)
               (lambda ()
                 (letrec ((var1 1)
                          (var2 var1))
                   'result)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((var1 var2)
                          (var2 2))
                   'result)))
;; all variables are kept unbound until body evaluation
(assert-equal? (tn)
               '(#f #f #f)
               (letrec ((var1 (symbol-bound? 'var1))
                        (var2 (symbol-bound? 'var1))
                        (var3 (symbol-bound? 'var1)))
                 (list var1 var2 var3)))
(assert-equal? (tn)
               '(#f #f #f)
               (letrec ((var1 (symbol-bound? 'var2))
                        (var2 (symbol-bound? 'var2))
                        (var3 (symbol-bound? 'var2)))
                 (list var1 var2 var3)))
(assert-equal? (tn)
               '(#f #f #f)
               (letrec ((var1 (symbol-bound? 'var3))
                        (var2 (symbol-bound? 'var3))
                        (var3 (symbol-bound? 'var3)))
                 (list var1 var2 var3)))
;; all variables can be referred from any position of the bindings
(assert-equal? (tn)
               '(#t #t #t)
               (letrec ((var1 (lambda () var1))
                        (var2 (lambda () var1))
                        (var3 (lambda () var1)))
                 (list (eq? (var1) var1)
                       (eq? (var2) var1)
                       (eq? (var3) var1))))
(assert-equal? (tn)
               '(#t #t #t)
               (letrec ((var1 (lambda () var2))
                        (var2 (lambda () var2))
                        (var3 (lambda () var2)))
                 (list (eq? (var1) var2)
                       (eq? (var2) var2)
                       (eq? (var3) var2))))
(assert-equal? (tn)
               '(#t #t #t)
               (letrec ((var1 (lambda () var3))
                        (var2 (lambda () var3))
                        (var3 (lambda () var3)))
                 (list (eq? (var1) var3)
                       (eq? (var2) var3)
                       (eq? (var3) var3))))

(tn "letrec internal definitions lacking sequence part")
;; at least one <expression> is required
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define var1 1))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define (proc1) 1))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define var1 1)
                   (define var2 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define (proc1) 1)
                   (define (proc2) 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define var1 1)
                   (define (proc2) 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define (proc1) 1)
                   (define var2 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     (define var2 2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define (proc2) 2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     (define (proc2) 2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define var2 2)))))
;; appending a non-definition expression into a begin block is invalid
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     'val))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     'val))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     (define var2 2)
                     'val))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define (proc2) 2)
                     'val))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     (define (proc2) 2)
                     'val))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define var2 2)
                     'val))))

(tn "letrec internal definitions cross reference")
;; R5RS: 5.2.2 Internal definitions
;; Just as for the equivalent `letrec' expression, it must be possible to
;; evaluate each <expression> of every internal definition in a <body> without
;; assigning or referring to the value of any <variable> being defined.
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define var1 1)
                   (define var2 var1)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define var1 var2)
                   (define var2 2)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (define var1 var1)
                   'val)))
(assert-equal? (tn)
               '(0 0 0 0 0)
               (letrec ((var0 0))
                 (define var1 var0)
                 (define var2 var0)
                 (begin
                   (define var3 var0)
                   (begin
                     (define var4 var0)))
                 (define var5 var0)
                 (list var1 var2 var3 var4 var5)))
(assert-equal? (tn)
               '(#f #f #f #f #f #f)
               (letrec ((var0 (symbol-bound? 'var1)))
                 (define var1 (symbol-bound? 'var1))
                 (define var2 (symbol-bound? 'var1))
                 (begin
                   (define var3 (symbol-bound? 'var1))
                   (begin
                     (define var4 (symbol-bound? 'var1))))
                 (define var5 (symbol-bound? 'var1))
                 (list var0 var1 var2 var3 var4 var5)))
(assert-equal? (tn)
               '(#f #f #f #f #f #f)
               (letrec ((var0 (symbol-bound? 'var2)))
                 (define var1 (symbol-bound? 'var2))
                 (define var2 (symbol-bound? 'var2))
                 (begin
                   (define var3 (symbol-bound? 'var2))
                   (begin
                     (define var4 (symbol-bound? 'var2))))
                 (define var5 (symbol-bound? 'var2))
                 (list var0 var1 var2 var3 var4 var5)))
(assert-equal? (tn)
               '(#f #f #f #f #f #f)
               (letrec ((var0 (symbol-bound? 'var3)))
                 (define var1 (symbol-bound? 'var3))
                 (define var2 (symbol-bound? 'var3))
                 (begin
                   (define var3 (symbol-bound? 'var3))
                   (begin
                     (define var4 (symbol-bound? 'var3))))
                 (define var5 (symbol-bound? 'var3))
                 (list var0 var1 var2 var3 var4 var5)))
(assert-equal? (tn)
               '(#f #f #f #f #f #f)
               (letrec ((var0 (symbol-bound? 'var4)))
                 (define var1 (symbol-bound? 'var4))
                 (define var2 (symbol-bound? 'var4))
                 (begin
                   (define var3 (symbol-bound? 'var4))
                   (begin
                     (define var4 (symbol-bound? 'var4))))
                 (define var5 (symbol-bound? 'var4))
                 (list var0 var1 var2 var3 var4 var5)))
(assert-equal? (tn)
               '(#f #f #f #f #f #f)
               (letrec ((var0 (symbol-bound? 'var5)))
                 (define var1 (symbol-bound? 'var5))
                 (define var2 (symbol-bound? 'var5))
                 (begin
                   (define var3 (symbol-bound? 'var5))
                   (begin
                     (define var4 (symbol-bound? 'var5))))
                 (define var5 (symbol-bound? 'var5))
                 (list var0 var1 var2 var3 var4 var5)))
;; outer let cannot refer internal variable even if letrec
(assert-error  (tn)
               (lambda ()
                 (letrec ((var0 (lambda () var1)))
                   (define var1 (lambda () 1))
                   (eq? (var0) var0))))
;; defining procedure can refer other (and self) variables as if letrec
(assert-equal? (tn)
               '(#t #t #t #t #t)
               (letrec ((var0 (lambda () 0)))
                 (define var1 (lambda () var0))
                 (define var2 (lambda () var0))
                 (begin
                   (define var3 (lambda () var0))
                   (begin
                     (define var4 (lambda () var0))))
                 (define var5 (lambda () var0))
                 (list (eq? (var1) var0)
                       (eq? (var2) var0)
                       (eq? (var3) var0)
                       (eq? (var4) var0)
                       (eq? (var5) var0))))
(assert-equal? (tn)
               '(#t #t #t #t #t)
               (letrec ()
                 (define var1 (lambda () var1))
                 (define var2 (lambda () var1))
                 (begin
                   (define var3 (lambda () var1))
                   (begin
                     (define var4 (lambda () var1))))
                 (define var5 (lambda () var1))
                 (list (eq? (var1) var1)
                       (eq? (var2) var1)
                       (eq? (var3) var1)
                       (eq? (var4) var1)
                       (eq? (var5) var1))))
(assert-equal? (tn)
               '(#t #t #t #t #t)
               (letrec ()
                 (define var1 (lambda () var2))
                 (define var2 (lambda () var2))
                 (begin
                   (define var3 (lambda () var2))
                   (begin
                     (define var4 (lambda () var2))))
                 (define var5 (lambda () var2))
                 (list (eq? (var1) var2)
                       (eq? (var2) var2)
                       (eq? (var3) var2)
                       (eq? (var4) var2)
                       (eq? (var5) var2))))
(assert-equal? (tn)
               '(#t #t #t #t #t)
               (letrec ()
                 (define var1 (lambda () var3))
                 (define var2 (lambda () var3))
                 (begin
                   (define var3 (lambda () var3))
                   (begin
                     (define var4 (lambda () var3))))
                 (define var5 (lambda () var3))
                 (list (eq? (var1) var3)
                       (eq? (var2) var3)
                       (eq? (var3) var3)
                       (eq? (var4) var3)
                       (eq? (var5) var3))))
(assert-equal? (tn)
               '(#t #t #t #t #t)
               (letrec ()
                 (define var1 (lambda () var4))
                 (define var2 (lambda () var4))
                 (begin
                   (define var3 (lambda () var4))
                   (begin
                     (define var4 (lambda () var4))))
                 (define var5 (lambda () var4))
                 (list (eq? (var1) var4)
                       (eq? (var2) var4)
                       (eq? (var3) var4)
                       (eq? (var4) var4)
                       (eq? (var5) var4))))
(assert-equal? (tn)
               '(#t #t #t #t #t)
               (letrec ()
                 (define var1 (lambda () var5))
                 (define var2 (lambda () var5))
                 (begin
                   (define var3 (lambda () var5))
                   (begin
                     (define var4 (lambda () var5))))
                 (define var5 (lambda () var5))
                 (list (eq? (var1) var5)
                       (eq? (var2) var5)
                       (eq? (var3) var5)
                       (eq? (var4) var5)
                       (eq? (var5) var5))))

(tn "letrec internal definitions valid forms")
;; valid internal definitions
(assert-equal? (tn)
               '(1)
               (letrec ()
                 (define var1 1)
                 (list var1)))
(assert-equal? (tn)
               '(1)
               (letrec ()
                 (define (proc1) 1)
                 (list (proc1))))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (define var1 1)
                 (define var2 2)
                 (list var1 var2)))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (define (proc1) 1)
                 (define (proc2) 2)
                 (list (proc1) (proc2))))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (define var1 1)
                 (define (proc2) 2)
                 (list var1 (proc2))))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (define (proc1) 1)
                 (define var2 2)
                 (list (proc1) var2)))
;; SigScheme accepts '(begin)' as valid internal definition '(begin
;; <definition>*)' as defined in "7.1.6 Programs and definitions" of R5RS
;; although it is rejected as expression '(begin <sequence>)' as defined in
;; "7.1.3 Expressions".
(assert-equal? (tn)
               1
               (letrec ()
                 (begin)
                 1))
(assert-equal? (tn)
               1
               (letrec ()
                 (begin)
                 (define var1 1)
                 (begin)
                 1))
(assert-equal? (tn)
               '(1)
               (letrec ()
                 (begin
                   (define var1 1))
                 (list var1)))
(assert-equal? (tn)
               '(1)
               (letrec ()
                 (begin
                   (define (proc1) 1))
                 (list (proc1))))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (begin
                   (define var1 1)
                   (define var2 2))
                 (list var1 var2)))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (begin
                   (define (proc1) 1)
                   (define (proc2) 2))
                 (list (proc1) (proc2))))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (begin
                   (define var1 1)
                   (define (proc2) 2))
                 (list var1 (proc2))))
(assert-equal? (tn)
               '(1 2)
               (letrec ()
                 (begin
                   (define (proc1) 1)
                   (define var2 2))
                 (list (proc1) var2)))
(assert-equal? (tn)
               '(1 2 3 4 5 6)
               (letrec ()
                 (begin
                   (define (proc1) 1)
                   (define var2 2)
                   (begin
                     (define (proc3) 3)
                     (define var4 4)
                     (begin
                       (define (proc5) 5)
                       (define var6 6))))
                 (list (proc1) var2
                       (proc3) var4
                       (proc5) var6)))
;; begin block and single definition mixed
(assert-equal? (tn)
               '(1 2 3 4 5 6)
               (letrec ()
                 (begin)
                 (define (proc1) 1)
                 (begin
                   (define var2 2)
                   (begin
                     (define (proc3) 3)
                     (begin)
                     (define var4 4)))
                 (begin)
                 (define (proc5) 5)
                 (begin
                   (begin
                     (begin
                       (begin)))
                   (define var6 6)
                   (begin))
                 (begin)
                 (list (proc1) var2
                       (proc3) var4
                       (proc5) var6)))

(tn "letrec internal definitions invalid begin blocks")
;; appending a non-definition expression into a begin block is invalid
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     'val)
                   (list var1))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     'val)
                   (list (proc1)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     (define var2 2)
                     'val)
                   (list var1 var2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define (proc2) 2)
                     'val)
                   (list (proc1) (proc2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define var1 1)
                     (define (proc2) 2)
                     'val)
                   (list var1 (proc2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define var2 2)
                     'val)
                   (list (proc1) var2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define var2 2)
                     (begin
                       (define (proc3) 3)
                       (define var4 4)
                       (begin
                         (define (proc5) 5)
                         (define var6 6)
                         'val)))
                   (list (proc1) var2
                         (proc3) var4
                         (proc5) var6))))

(tn "letrec internal definitions invalid placement")
;; a non-definition expression prior to internal definition is invalid
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define var1 1))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define (proc1) 1))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define var1 1)
                   (define var2 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define (proc1) 1)
                   (define (proc2) 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define var1 1)
                   (define (proc2) 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define (proc1) 1)
                   (define var2 2))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define var1 1)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define var1 1)
                     (define var2 2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1)
                     (define (proc2) 2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define var1 1)
                     (define (proc2) 2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1)
                     (define var2 2)))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1)
                     (define var2 2)
                     (begin
                       (define (proc3) 3)
                       (define var4 4)
                       (begin
                         (define (proc5) 5)
                         (define var6 6)))))))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   (begin
                     (define (proc1) 1)
                     (define var2 2)
                     'val
                     (begin
                       (define (proc3) 3)
                       (define var4 4)
                       (begin
                         (define (proc5) 5)
                         (define var6 6)))))))
;; a non-definition expression prior to internal definition is invalid even if
;; expression(s) is following the internal definition
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define var1 1)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define (proc1) 1)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define var1 1)
                   (define var2 2)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define (proc1) 1)
                   (define (proc2) 2)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define var1 1)
                   (define (proc2) 2)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (define (proc1) 1)
                   (define var2 2)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin)
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define var1 1))
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1))
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define var1 1)
                     (define var2 2))
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1)
                     (define (proc2) 2))
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define var1 1)
                     (define (proc2) 2))
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1)
                     (define var2 2))
                   'val)))
(assert-error  (tn)
               (lambda ()
                 (letrec ()
                   'val
                   (begin
                     (define (proc1) 1)
                     (define var2 2)
                     (begin
                       (define (proc3) 3)
                       (define var4 4)
                       (begin
                         (define (proc5) 5)
                         (define var6 6))))
                   (list (proc1) var2
                         (proc3) var4
                         (proc5) var6))))

(tn "letrec binding syntactic keywords")
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn define))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn if))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn and))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn cond))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn begin))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn do))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn delay))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn let*))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn else))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn =>))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn quote))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn quasiquote))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn unquote))
                   #t)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((syn unquote-splicing))
                   #t)))


(tn "letrec")
;; empty bindings is allowed by the formal syntax spec
(assert-equal? (tn)
               'result
               (letrec () 'result))
;; duplicate variable name
(assert-error  (tn)
               (lambda ()
                 (letrec ((var1 1)
                          (var1 2))
                   'result)))
;; masked variable name
(assert-equal? (tn)
               '(#t #t #t #t #f #f #t #t #f #t)
               (letrec ((var1 (lambda () var3))
                        (var2 (lambda () var4))
                        (var3 (lambda () var3))
                        (var4 (lambda () var4))
                        (var1in #f)
                        (var2in #f)
                        (var5in #f))
                 (letrec ((var1 (lambda () var1))
                          (var2 (lambda () var1))
                          (var5 (lambda () var3)))
                   (set! var1in var1)
                   (set! var2in var2)
                   (set! var5in var5))
                 (list (eq? (var1) var3)
                       (eq? (var2) var4)
                       (eq? (var3) var3)
                       (eq? (var4) var4)
                       (eq? (var1in) var1)
                       (eq? (var2in) var1)
                       (eq? (var1in) var1in)
                       (eq? (var2in) var1in)
                       (eq? (var2in) var2in)
                       (eq? (var5in) var3))))
(assert-equal? (tn)
               '(4 5 3)
               (letrec ((var1 1)
                        (var2 2)
                        (var3 3))
                 (letrec ((var1 4)
                          (var2 5))
                   (list var1 var2 var3))))
(assert-equal? (tn)
               '(1 2 3)
               (letrec ((var1 1)
                        (var2 2)
                        (var3 3))
                 (letrec ((var1 4)
                          (var2 5))
                   'dummy)
                 (list var1 var2 var3)))
(assert-equal? (tn)
               '(1 2 9)
               (letrec ((var1 1)
                        (var2 2)
                        (var3 3))
                 (letrec ((var1 4)
                          (var2 5))
                   (set! var3 (+ var1 var2)))
                 (list var1 var2 var3)))
(assert-equal? (tn)
               '(1 2 30)
               (letrec ((var1 1)
                        (var2 2)
                        (var3 3))
                 (letrec ((var1 4)
                          (var2 5))
                   (set! var1 10)
                   (set! var2 20)
                   (set! var3 (+ var1 var2)))
                 (list var1 var2 var3)))
(assert-equal? (tn)
               '(1 2 3 (10 20))
               (letrec ((var1 1)
                        (var2 2)
                        (var3 3)
                        (var4 (letrec ((var1 4)
                                           (var2 5))
                                    (set! var1 10)
                                    (set! var2 20)
                                    (list var1 var2))))
                 (list var1 var2 var3 var4)))
(assert-error  (tn)
               (lambda ()
                 (letrec ((var1 1)
                          (var2 2)
                          (var3 3)
                          (var4 (letrec ((var1 4)
                                             (var2 5))
                                      (set! var3 10))))
                   (list var1 var2 var3 var4))))
;; variable reference
(assert-equal? (tn)
               3
               (letrec ((proc (lambda () var))
                        (var  3))
                 (proc)))
;; ordinary recursions
(assert-equal? (tn)
               4
               (letrec ((proc1 (lambda (n) (+ n 1)))
                        (proc2 (lambda (n) (proc1 n))))
                 (proc2 3)))
(assert-equal? (tn)
               6
               (letrec ((proc1 (lambda (n) (proc2 n)))
                        (proc2 (lambda (n) (+ n 1))))
                 (proc1 5)))
(assert-equal? (tn)
               #t
               (letrec ((even?
                         (lambda (n)
                           (if (zero? n)
                               #t
                               (odd? (- n 1)))))
                        (odd?
                         (lambda (n)
                           (if (zero? n)
                               #f
                               (even? (- n 1))))))
                 (even? 88)))
(assert-equal? (tn)
               #f
               (letrec ((even?
                         (lambda (n)
                           (if (zero? n)
                               #t
                               (odd? (- n 1)))))
                        (odd?
                         (lambda (n)
                           (if (zero? n)
                               #f
                               (even? (- n 1))))))
                 (odd? 88)))

(tn "letrec lexical scope")
(define count-letrec
  (letrec ((count-letrec 0))  ;; intentionally same name
    (lambda ()
      (set! count-letrec (+ count-letrec 1))
      count-letrec)))
(assert-true   (tn) (procedure? count-letrec))
(assert-equal? (tn) 1 (count-letrec))
(assert-equal? (tn) 2 (count-letrec))
(assert-equal? (tn) 3 (count-letrec))


(total-report)
