#! /usr/bin/env sscm -C Shift_JIS
;; -*- buffer-file-coding-system: shift_jisx0213 -*-
;; C-x RET c shift_jisx0213 C-x C-f test-enc-sjis.scm

;;  Filename : test-enc-sjis.scm
;;  About    : unit test for SJIS string
;;
;;  Copyright (C) 2005-2006 Kazuki Ohta <mover AT hct.zaq.ne.jp>
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

(if (not (and (provided? "shift-jis")
              (symbol-bound? 'char?)
              (symbol-bound? 'string?)))
    (test-skip "Shift_JIS codec is not enabled"))

(define tn test-name)

(assert-equal? "string 1" "���l�ɂ�" (string #\�� #\�l #\�� #\��))
(assert-equal? "list->string 1" "3����" (list->string '(#\3 #\�� #\��)))
(assert-equal? "string->list 1" '(#\�� #\�� #\��) (string->list "������"))

(assert-equal? "string-ref 1" #\��  (string-ref "��hi��͕�" 3))
(assert-equal? "make-string 1" "����������"   (make-string 5 #\��))
(assert-equal? "string-copy 1"     "���⍁"   (string-copy "���⍁"))
(assert-equal? "string-set! 1"     "���j��"   (let ((s (string-copy "���j��")))
                                                (string-set! s 2 #\��)
                                                s))




;; The character after �� is in JIS X 0213 plane 2.
(define str1 "��˃�ah�\\\�\n!!���@!")
(define str1-list '(#\�� #\� #\�� #\a #\h #\�\ #\\ #\�\ #\n #\! #\! #\�� #\�@ #\!))

(assert-equal? "string 2" str1 (apply string str1-list))
(assert-equal? "list->string 2" str1-list (string->list str1))

;; JIS X 0201 kana (single byte)
(assert-equal? "JIS X 0201 kana" #\� (integer->char #xcb))
(assert-equal? "JIS X 0201 kana" #xcb (char->integer #\�))
(assert-equal? "JIS X 0201 kana" '(#\�) (string->list "�"))
(assert-equal? "JIS X 0201 kana" "�" (list->string '(#\�)))

(assert-equal? "JIS X 0208 kana #1" #\�� (integer->char #x8384))
(assert-equal? "JIS X 0208 kana #2" (car (string->list "��")) (integer->char #x8384))
(assert-equal? "JIS X 0208 kana #3" #x8384 (char->integer #\��))
(assert-equal? "JIS X 0208 kana #4" #x8384 (char->integer (integer->char #x8384)))
(assert-equal? "JIS X 0208 kana #5" '(#\��) (string->list "��"))
(assert-equal? "JIS X 0208 kana #6" "��" (list->string '(#\��)))
(assert-equal? "JIS X 0208 kana #7" "��" (list->string (string->list "��")))

(assert-equal? "JIS X 0201 kana and 0208 kana" '(#\� #\��) (string->list "˃�"))
(assert-equal? "JIS X 0201 kana and 0208 kana" "˃�" (list->string '(#\� #\��)))

;; SRFI-75
(tn "SRFI-75")
(assert-parseable   (tn) "#\\x63")
(assert-parse-error (tn) "#\\u0063")
(assert-parse-error (tn) "#\\U00000063")

(assert-parse-error (tn) "\"\\x63\"")
(assert-parse-error (tn) "\"\\u0063\"")
(assert-parse-error (tn) "\"\\U00000063\"")

(assert-parseable   (tn) "'a")
;; Non-Unicode multibyte symbols are not allowed.
(assert-parse-error (tn) "'��")

(tn "R6RS (R5.92RS) chars")
(assert-parseable   (tn) "#\\x")
(assert-parseable   (tn) "#\\x6")
(assert-parseable   (tn) "#\\xf")
(assert-parseable   (tn) "#\\x63")
(assert-parseable   (tn) "#\\x063")
(assert-parseable   (tn) "#\\x0063")
(assert-parseable   (tn) "#\\x00063")
(assert-parseable   (tn) "#\\x0000063")
(assert-parseable   (tn) "#\\x00000063")
(assert-parse-error (tn) "#\\x000000063")

(assert-parseable   (tn) "#\\x3042")

(assert-parse-error (tn) "#\\x-")
(assert-parse-error (tn) "#\\x-6")
(assert-parse-error (tn) "#\\x-f")
(assert-parse-error (tn) "#\\x-63")
(assert-parse-error (tn) "#\\x-063")
(assert-parse-error (tn) "#\\x-0063")
(assert-parse-error (tn) "#\\x-00063")
(assert-parse-error (tn) "#\\x-0000063")
(assert-parse-error (tn) "#\\x-00000063")
(assert-parse-error (tn) "#\\x-000000063")

(assert-parse-error (tn) "#\\x+")
(assert-parse-error (tn) "#\\x+6")
(assert-parse-error (tn) "#\\x+f")
(assert-parse-error (tn) "#\\x+63")
(assert-parse-error (tn) "#\\x+063")
(assert-parse-error (tn) "#\\x+0063")
(assert-parse-error (tn) "#\\x+00063")
(assert-parse-error (tn) "#\\x+0000063")
(assert-parse-error (tn) "#\\x+00000063")
(assert-parse-error (tn) "#\\x+000000063")

(tn "R6RS (R5.92RS) string hex escapes")
(assert-parse-error (tn) "\"\\x\"")
(assert-parse-error (tn) "\"\\x6\"")
(assert-parse-error (tn) "\"\\xf\"")
(assert-parse-error (tn) "\"\\x63\"")
(assert-parse-error (tn) "\"\\x063\"")
(assert-parse-error (tn) "\"\\x0063\"")
(assert-parse-error (tn) "\"\\x00063\"")
(assert-parse-error (tn) "\"\\x0000063\"")
(assert-parse-error (tn) "\"\\x00000063\"")
(assert-parse-error (tn) "\"\\x000000063\"")

(assert-parse-error (tn) "\"\\x;\"")
(assert-parseable   (tn) "\"\\x6;\"")
(assert-parseable   (tn) "\"\\xf;\"")
(assert-parseable   (tn) "\"\\x63;\"")
(assert-parseable   (tn) "\"\\x063;\"")
(assert-parseable   (tn) "\"\\x0063;\"")
(assert-parseable   (tn) "\"\\x00063;\"")
(assert-parseable   (tn) "\"\\x0000063;\"")
(assert-parseable   (tn) "\"\\x00000063;\"")
(assert-parse-error (tn) "\"\\x000000063;\"")

(assert-parse-error (tn) "\"\\x-\"")
(assert-parse-error (tn) "\"\\x-6\"")
(assert-parse-error (tn) "\"\\x-f\"")
(assert-parse-error (tn) "\"\\x-63\"")
(assert-parse-error (tn) "\"\\x-063\"")
(assert-parse-error (tn) "\"\\x-0063\"")
(assert-parse-error (tn) "\"\\x-00063\"")
(assert-parse-error (tn) "\"\\x-0000063\"")
(assert-parse-error (tn) "\"\\x-00000063\"")
(assert-parse-error (tn) "\"\\x-000000063\"")

(assert-parse-error (tn) "\"\\x-;\"")
(assert-parse-error (tn) "\"\\x-6;\"")
(assert-parse-error (tn) "\"\\x-f;\"")
(assert-parse-error (tn) "\"\\x-63;\"")
(assert-parse-error (tn) "\"\\x-063;\"")
(assert-parse-error (tn) "\"\\x-0063;\"")
(assert-parse-error (tn) "\"\\x-00063;\"")
(assert-parse-error (tn) "\"\\x-0000063;\"")
(assert-parse-error (tn) "\"\\x-00000063;\"")
(assert-parse-error (tn) "\"\\x-000000063;\"")

(assert-parse-error (tn) "\"\\x+\"")
(assert-parse-error (tn) "\"\\x+6\"")
(assert-parse-error (tn) "\"\\x+f\"")
(assert-parse-error (tn) "\"\\x+63\"")
(assert-parse-error (tn) "\"\\x+063\"")
(assert-parse-error (tn) "\"\\x+0063\"")
(assert-parse-error (tn) "\"\\x+00063\"")
(assert-parse-error (tn) "\"\\x+0000063\"")
(assert-parse-error (tn) "\"\\x+00000063\"")
(assert-parse-error (tn) "\"\\x+000000063\"")

(assert-parse-error (tn) "\"\\x+;\"")
(assert-parse-error (tn) "\"\\x+6;\"")
(assert-parse-error (tn) "\"\\x+f;\"")
(assert-parse-error (tn) "\"\\x+63;\"")
(assert-parse-error (tn) "\"\\x+063;\"")
(assert-parse-error (tn) "\"\\x+0063;\"")
(assert-parse-error (tn) "\"\\x+00063;\"")
(assert-parse-error (tn) "\"\\x+0000063;\"")
(assert-parse-error (tn) "\"\\x+00000063;\"")
(assert-parse-error (tn) "\"\\x+000000063;\"")

(total-report)
