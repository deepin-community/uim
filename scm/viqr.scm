;;;
;;; Copyright (c) 2003-2013 uim Project https://github.com/uim/uim
;;;
;;; All rights reserved.
;;;
;;; Redistribution and use in source and binary forms, with or without
;;; modification, are permitted provided that the following conditions
;;; are met:
;;; 1. Redistributions of source code must retain the above copyright
;;;    notice, this list of conditions and the following disclaimer.
;;; 2. Redistributions in binary form must reproduce the above copyright
;;;    notice, this list of conditions and the following disclaimer in the
;;;    documentation and/or other materials provided with the distribution.
;;; 3. Neither the name of authors nor the names of its contributors
;;;    may be used to endorse or promote products derived from this software
;;;    without specific prior written permission.
;;;
;;; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
;;; ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;;; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;;; ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE
;;; FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;;; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
;;; OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
;;; HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
;;; LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
;;; OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
;;; SUCH DAMAGE.
;;;;

(require "generic.scm")

(define viqr-rule
  '(
((("A" ))("A"))
((("A" "'" ))("Á"))
((("A" "(" ))("Ă"))
((("A" "(" "'" ))("Ắ"))
((("A" "(" "." ))("Ặ"))
((("A" "(" "?" ))("Ẳ"))
((("A" "(" "`" ))("Ằ"))
((("A" "(" "~" ))("Ẵ"))
((("A" "." ))("Ạ"))
((("A" "?" ))("Ả"))
((("A" "^" ))("Â"))
((("A" "^" "'" ))("Ấ"))
((("A" "^" "." ))("Ậ"))
((("A" "^" "?" ))("Ẩ"))
((("A" "^" "`" ))("Ầ"))
((("A" "^" "~" ))("Ẫ"))
((("A" "`" ))("À"))
((("A" "~" ))("Ã"))
((("D" ))("D"))
((("D" "D" ))("Đ"))
((("D" "d" ))("Đ"))
((("E" ))("E"))
((("E" "'" ))("É"))
((("E" "." ))("Ẹ"))
((("E" "?" ))("Ẻ"))
((("E" "^" ))("Ê"))
((("E" "^" "'" ))("Ế"))
((("E" "^" "." ))("Ệ"))
((("E" "^" "?" ))("Ể"))
((("E" "^" "`" ))("Ề"))
((("E" "^" "~" ))("Ễ"))
((("E" "`" ))("È"))
((("E" "~" ))("Ẽ"))
((("I" ))("I"))
((("I" "'" ))("Í"))
((("I" "." ))("Ị"))
((("I" "?" ))("Ỉ"))
((("I" "`" ))("Ì"))
((("I" "~" ))("Ĩ"))
((("O" ))("O"))
((("O" "'" ))("Ó"))
((("O" "+" ))("Ơ"))
((("O" "+" "'" ))("Ớ"))
((("O" "+" "." ))("Ợ"))
((("O" "+" "?" ))("Ở"))
((("O" "+" "`" ))("Ờ"))
((("O" "+" "~" ))("Ỡ"))
((("O" "." ))("Ọ"))
((("O" "?" ))("Ỏ"))
((("O" "^" ))("Ô"))
((("O" "^" "'" ))("Ố"))
((("O" "^" "." ))("Ộ"))
((("O" "^" "?" ))("Ổ"))
((("O" "^" "`" ))("Ồ"))
((("O" "^" "~" ))("Ỗ"))
((("O" "`" ))("Ò"))
((("O" "~" ))("Õ"))
((("U" ))("U"))
((("U" "'" ))("Ú"))
((("U" "+" ))("Ư"))
((("U" "+" "'" ))("Ứ"))
((("U" "+" "." ))("Ự"))
((("U" "+" "?" ))("Ử"))
((("U" "+" "`" ))("Ừ"))
((("U" "+" "~" ))("Ữ"))
((("U" "." ))("Ụ"))
((("U" "?" ))("Ủ"))
((("U" "`" ))("Ù"))
((("U" "~" ))("Ũ"))
((("Y" ))("Y"))
((("Y" "'" ))("Ý"))
((("Y" "." ))("Ỵ"))
((("Y" "?" ))("Ỷ"))
((("Y" "`" ))("Ỳ"))
((("Y" "~" ))("Ỹ"))
((("\\" ))(""))
((("\\" "'" ))("'"))
((("\\" "(" ))("("))
((("\\" "+" ))("+"))
((("\\" "." ))("."))
((("\\" "?" ))("?"))
((("\\" "D" ))("D"))
((("\\" "\\" ))("\\"))
((("\\" "^" ))("^"))
((("\\" "`" ))("`"))
((("\\" "d" ))("d"))
((("\\" "~" ))("~"))
((("a" ))("a"))
((("a" "'" ))("á"))
((("a" "(" ))("ă"))
((("a" "(" "'" ))("ắ"))
((("a" "(" "." ))("ặ"))
((("a" "(" "?" ))("ẳ"))
((("a" "(" "`" ))("ằ"))
((("a" "(" "~" ))("ẵ"))
((("a" "." ))("ạ"))
((("a" "?" ))("ả"))
((("a" "^" ))("â"))
((("a" "^" "'" ))("ấ"))
((("a" "^" "." ))("ậ"))
((("a" "^" "?" ))("ẩ"))
((("a" "^" "`" ))("ầ"))
((("a" "^" "~" ))("ẫ"))
((("a" "`" ))("à"))
((("a" "~" ))("ã"))
((("d" ))("d"))
((("d" "d" ))("đ"))
((("e" ))("e"))
((("e" "'" ))("é"))
((("e" "." ))("ẹ"))
((("e" "?" ))("ẻ"))
((("e" "^" ))("ê"))
((("e" "^" "'" ))("ế"))
((("e" "^" "." ))("ệ"))
((("e" "^" "?" ))("ể"))
((("e" "^" "`" ))("ề"))
((("e" "^" "~" ))("ễ"))
((("e" "`" ))("è"))
((("e" "~" ))("ẽ"))
((("i" ))("i"))
((("i" "'" ))("í"))
((("i" "." ))("ị"))
((("i" "?" ))("ỉ"))
((("i" "`" ))("ì"))
((("i" "~" ))("ĩ"))
((("o" ))("o"))
((("o" "'" ))("ó"))
((("o" "+" ))("ơ"))
((("o" "+" "'" ))("ớ"))
((("o" "+" "." ))("ợ"))
((("o" "+" "?" ))("ở"))
((("o" "+" "`" ))("ờ"))
((("o" "+" "~" ))("ỡ"))
((("o" "." ))("ọ"))
((("o" "?" ))("ỏ"))
((("o" "^" ))("ô"))
((("o" "^" "'" ))("ố"))
((("o" "^" "." ))("ộ"))
((("o" "^" "?" ))("ổ"))
((("o" "^" "`" ))("ồ"))
((("o" "^" "~" ))("ỗ"))
((("o" "`" ))("ò"))
((("o" "~" ))("õ"))
((("u" ))("u"))
((("u" "'" ))("ú"))
((("u" "+" ))("ư"))
((("u" "+" "'" ))("ứ"))
((("u" "+" "." ))("ự"))
((("u" "+" "?" ))("ử"))
((("u" "+" "`" ))("ừ"))
((("u" "+" "~" ))("ữ"))
((("u" "." ))("ụ"))
((("u" "?" ))("ủ"))
((("u" "`" ))("ù"))
((("u" "~" ))("ũ"))
((("y" ))("y"))
((("y" "'" ))("ý"))
((("y" "." ))("ỵ"))
((("y" "?" ))("ỷ"))
((("y" "`" ))("ỳ"))
((("y" "~" ))("ỹ"))))


(define viqr-init-handler
  (lambda (id im arg)
    (generic-context-new id im viqr-rule #f)))

(generic-register-im
 'viqr
 "vi"
 "UTF-8"
 (N_ "VIQR")
 (N_ "VIetnamese Quoted-Readable")
 viqr-init-handler)