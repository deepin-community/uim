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

;; ja-kana-hiragana rule and ja-kana-katakana-rule should be merged.

(define ja-kana-hiragana-rule
  '(
    ((("#"). ("??"))())
    ((("E"). ("??"))())
    ((("$"). ("??"))())
    ((("%"). ("??"))())
    ((("&"). ("??"))())
    ((("'"). ("??"))())
    ((("("). ("??"))())
    (((")"). ("??"))())
    ((("~"). ("??"))())
    ((("Z"). ("??"))())
    ((("y"). ("??"))())
    ((("3"). ("??"))())
    ((("e"). ("??"))())
    ((("4"). ("??"))())
    ((("5"). ("??"))())
    ((("6"). ("??"))())
    ((("t"). ("??"))())
    ((("g"). ("??"))())
    ((("h"). ("??"))())
    (((":"). ("??"))())
    ((("b"). ("??"))())
    ((("x"). ("??"))())
    ((("d"). ("??"))())
    ((("r"). ("??"))())
    ((("p"). ("??"))())
    ((("c"). ("??"))())
    ((("q"). ("??"))())
    ((("a"). ("??"))())
    ((("z"). ("??"))())
    ((("w"). ("??"))())
    ((("s"). ("??"))())
    ((("u"). ("??"))())
    ((("i"). ("??"))())
    ((("1"). ("??"))())
    (((","). ("??"))())
    ((("k"). ("??"))())
    ((("f"). ("??"))())
    ((("v"). ("??"))())
    ((("2"). ("??"))())
    ((("^"). ("??"))())
    ((("-"). ("??"))())
    ((("j"). ("??"))())
    ((("n"). ("??"))())
    ((("]"). ("??"))())
    ((("/"). ("??"))())
    ((("m"). ("??"))())
    ((("7"). ("??"))())
    ((("8"). ("??"))())
    ((("9"). ("??"))())
    ((("o"). ("??"))())
    ((("l"). ("??"))())
    ((("."). ("??"))())
    (((";"). ("??"))())
    ((("0"). ("??"))())
    ((("|"). ("??"))())
    ((("T"). ("??"))())
    ((("G"). ("??"))())
    ((("H"). ("??"))())
    ((("*"). ("??"))())
    ((("B"). ("??"))())
    ((("X"). ("??"))())
    ((("D"). ("??"))())
    ((("R"). ("??"))())
    ((("P"). ("??"))())
    ((("C"). ("??"))())
    ((("Q"). ("??"))())
    ((("A"). ("??"))())
    ((("W"). ("??"))())
    ((("S"). ("??"))())
    ((("U"). ("??"))())
    ((("I"). ("??"))())
    ((("!"). ("??"))())
    ((("K"). ("??"))())
    ((("F"). ("??"))())
    ((("V"). ("??"))())
    ((("\""). ("??"))())
    ((("="). ("??"))())
    ((("J"). ("??"))())
    ((("N"). ("??"))())
    ((("M"). ("??"))())
    ((("O"). ("??"))())
    ((("L"). ("??"))())
    ((("+"). ("??"))())
    ((("_"). ("??"))())
    ((("Y"). ("??"))())
    ((("\\"). ("??"))())
    ((("yen"). ("??"))())

    ((("kana-a"). ("??"))())
    ((("kana-i"). ("??"))())
    ((("kana-u"). ("??"))())
    ((("kana-e"). ("??"))())
    ((("kana-o"). ("??"))())
    ((("kana-ya"). ("??"))())
    ((("kana-yu"). ("??"))())
    ((("kana-yo"). ("??"))())
    ((("kana-WO"). ("??"))())
    ((("kana-tsu"). ("??"))())
    ((("kana-N"). ("??"))())
    ((("kana-A"). ("??"))())
    ((("kana-I"). ("??"))())
    ((("kana-U"). ("??"))())
    ((("kana-E"). ("??"))())
    ((("kana-O"). ("??"))())
    ((("kana-KA"). ("??"))())
    ((("kana-KI"). ("??"))())
    ((("kana-KU"). ("??"))())
    ((("kana-KE"). ("??"))())
    ((("kana-KO"). ("??"))())
    ((("kana-SA"). ("??"))())
    ((("kana-SHI"). ("??"))())
    ((("kana-SU"). ("??"))())
    ((("kana-SE"). ("??"))())
    ((("kana-SO"). ("??"))())
    ((("kana-TA"). ("??"))())
    ((("kana-CHI"). ("??"))())
    ((("kana-TSU"). ("??"))())
    ((("kana-TE"). ("??"))())
    ((("kana-TO"). ("??"))())
    ((("kana-NA"). ("??"))())
    ((("kana-NI"). ("??"))())
    ((("kana-NU"). ("??"))())
    ((("kana-NE"). ("??"))())
    ((("kana-NO"). ("??"))())
    ((("kana-HA"). ("??"))())
    ((("kana-HI"). ("??"))())
    ((("kana-FU"). ("??"))())
    ((("kana-HE"). ("??"))())
    ((("kana-HO"). ("??"))())
    ((("kana-MA"). ("??"))())
    ((("kana-MI"). ("??"))())
    ((("kana-MU"). ("??"))())
    ((("kana-ME"). ("??"))())
    ((("kana-MO"). ("??"))())
    ((("kana-YA"). ("??"))())
    ((("kana-YU"). ("??"))())
    ((("kana-YO"). ("??"))())
    ((("kana-RA"). ("??"))())
    ((("kana-RI"). ("??"))())
    ((("kana-RU"). ("??"))())
    ((("kana-RE"). ("??"))())
    ((("kana-RO"). ("??"))())
    ((("kana-WA"). ("??"))())
    ((("kana-prolonged-sound"). ("??"))())

    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "@"). ())("??" ""))
    ((("??" "["). ())("??" ""))
    ((("??" "["). ())("??" ""))
    ((("??" "["). ())("??" ""))
    ((("??" "["). ())("??" ""))
    ((("??" "["). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))
    ((("??" "`"). ())("??" ""))

    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-voiced-sound"). ())("??" ""))
    ((("??" "kana-semivoiced-sound"). ())("??" ""))
    ((("??" "kana-semivoiced-sound"). ())("??" ""))
    ((("??" "kana-semivoiced-sound"). ())("??" ""))
    ((("??" "kana-semivoiced-sound"). ())("??" ""))
    ((("??" "kana-semivoiced-sound"). ())("??" ""))

    (((">"). ("??"))())
    ((("<"). ("??"))())
    ((("?"). ("??"))())
    ((("@"). ("??"))())
    ((("["). ("??"))())
    ((("{"). ("??"))())
    ((("}"). ("??"))())
    ((("`"). ("??"))())

    ((("kana-fullstop"). ("??"))())
    ((("kana-comma"). ("??"))())
    ((("kana-conjunctive"). ("??"))())
    ((("kana-voiced-sound"). ("??"))())
    ((("kana-semivoiced-sound"). ("??"))())
    ((("kana-opening-bracket"). ("??"))())
    ((("kana-closing-bracket"). ("??"))())

    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))

    ))

(define ja-kana-katakana-rule
  '(
    ((("#"). ("??"))())
    ((("E"). ("??"))())
    ((("$"). ("??"))())
    ((("%"). ("??"))())
    ((("&"). ("??"))())
    ((("'"). ("??"))())
    ((("("). ("??"))())
    (((")"). ("??"))())
    ((("~"). ("??"))())
    ((("Z"). ("??"))())
    ((("y"). ("??"))())
    ((("3"). ("??"))())
    ((("e"). ("??"))())
    ((("4"). ("??"))())
    ((("5"). ("??"))())
    ((("6"). ("??"))())
    ((("t"). ("??"))())
    ((("g"). ("??"))())
    ((("h"). ("??"))())
    (((":"). ("??"))())
    ((("b"). ("??"))())
    ((("x"). ("??"))())
    ((("d"). ("??"))())
    ((("r"). ("??"))())
    ((("p"). ("??"))())
    ((("c"). ("??"))())
    ((("q"). ("??"))())
    ((("a"). ("??"))())
    ((("z"). ("??"))())
    ((("w"). ("??"))())
    ((("s"). ("??"))())
    ((("u"). ("??"))())
    ((("i"). ("??"))())
    ((("1"). ("??"))())
    (((","). ("??"))())
    ((("k"). ("??"))())
    ((("f"). ("??"))())
    ((("v"). ("??"))())
    ((("2"). ("??"))())
    ((("^"). ("??"))())
    ((("-"). ("??"))())
    ((("j"). ("??"))())
    ((("n"). ("??"))())
    ((("]"). ("??"))())
    ((("/"). ("??"))())
    ((("m"). ("??"))())
    ((("7"). ("??"))())
    ((("8"). ("??"))())
    ((("9"). ("??"))())
    ((("o"). ("??"))())
    ((("l"). ("??"))())
    ((("."). ("??"))())
    (((";"). ("??"))())
    ((("0"). ("??"))())
    ((("|"). ("??"))())
    ((("T"). ("??"))())
    ((("G"). ("??"))())
    ((("H"). ("??"))())
    ((("*"). ("??"))())
    ((("B"). ("??"))())
    ((("X"). ("??"))())
    ((("D"). ("??"))())
    ((("R"). ("??"))())
    ((("P"). ("??"))())
    ((("C"). ("??"))())
    ((("Q"). ("??"))())
    ((("A"). ("??"))())
    ((("W"). ("??"))())
    ((("S"). ("??"))())
    ((("U"). ("??"))())
    ((("I"). ("??"))())
    ((("!"). ("??"))())
    ((("K"). ("??"))())
    ((("F"). ("??"))())
    ((("V"). ("??"))())
    ((("\""). ("??"))())
    ((("="). ("??"))())
    ((("J"). ("??"))())
    ((("N"). ("??"))())
    ((("M"). ("??"))())
    ((("O"). ("??"))())
    ((("L"). ("??"))())
    ((("+"). ("??"))())
    ((("_"). ("??"))())
    ((("Y"). ("??"))())
    ((("\\"). ("??"))())
    ((("yen"). ("??"))())

    ((("kana-a"). ("??"))())
    ((("kana-i"). ("??"))())
    ((("kana-u"). ("??"))())
    ((("kana-e"). ("??"))())
    ((("kana-o"). ("??"))())
    ((("kana-ya"). ("??"))())
    ((("kana-yu"). ("??"))())
    ((("kana-yo"). ("??"))())
    ((("kana-wo"). ("??"))())
    ((("kana-tsu"). ("??"))())
    ((("kana-N"). ("??"))())
    ((("kana-A"). ("??"))())
    ((("kana-I"). ("??"))())
    ((("kana-U"). ("??"))())
    ((("kana-E"). ("??"))())
    ((("kana-O"). ("??"))())
    ((("kana-KA"). ("??"))())
    ((("kana-KI"). ("??"))())
    ((("kana-KU"). ("??"))())
    ((("kana-KE"). ("??"))())
    ((("kana-KO"). ("??"))())
    ((("kana-SA"). ("??"))())
    ((("kana-SHI"). ("??"))())
    ((("kana-SU"). ("??"))())
    ((("kana-SE"). ("??"))())
    ((("kana-SO"). ("??"))())
    ((("kana-TA"). ("??"))())
    ((("kana-CHI"). ("??"))())
    ((("kana-TSU"). ("??"))())
    ((("kana-TE"). ("??"))())
    ((("kana-TO"). ("??"))())
    ((("kana-NA"). ("??"))())
    ((("kana-NI"). ("??"))())
    ((("kana-NU"). ("??"))())
    ((("kana-NE"). ("??"))())
    ((("kana-NO"). ("??"))())
    ((("kana-HA"). ("??"))())
    ((("kana-HI"). ("??"))())
    ((("kana-FU"). ("??"))())
    ((("kana-HE"). ("??"))())
    ((("kana-HO"). ("??"))())
    ((("kana-MA"). ("??"))())
    ((("kana-MI"). ("??"))())
    ((("kana-MU"). ("??"))())
    ((("kana-ME"). ("??"))())
    ((("kana-MO"). ("??"))())
    ((("kana-YA"). ("??"))())
    ((("kana-YU"). ("??"))())
    ((("kana-YO"). ("??"))())
    ((("kana-RA"). ("??"))())
    ((("kana-RI"). ("??"))())
    ((("kana-RU"). ("??"))())
    ((("kana-RE"). ("??"))())
    ((("kana-RO"). ("??"))())
    ((("kana-WA"). ("??"))())
    ((("kana-prolonged-sound"). ("??"))())

    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("??"))
    ((("??" "["). ())("??"))
    ((("??" "["). ())("??"))
    ((("??" "["). ())("??"))
    ((("??" "["). ())("??"))
    ((("??" "["). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("??"))

    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-semivoiced-sound"). ())("??"))
    ((("??" "kana-semivoiced-sound"). ())("??"))
    ((("??" "kana-semivoiced-sound"). ())("??"))
    ((("??" "kana-semivoiced-sound"). ())("??"))
    ((("??" "kana-semivoiced-sound"). ())("??"))

    (((">"). ("??"))())
    ((("<"). ("??"))())
    ((("?"). ("??"))())
    ((("@"). ("??"))())
    ((("["). ("??"))())
    ((("{"). ("??"))())
    ((("}"). ("??"))())
    ((("`"). ("??"))())

    ((("kana-fullstop"). ("??"))())
    ((("kana-comma"). ("??"))())
    ((("kana-conjunctive"). ("??"))())
    ((("kana-voiced-sound"). ("??"))())
    ((("kana-semivoiced-sound"). ("??"))())
    ((("kana-opening-bracket"). ("??"))())
    ((("kana-closing-bracket"). ("??"))())

    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ))

(define ja-kana-halfkana-rule
  '(
    ((("#"). ("??"))())
    ((("E"). ("??"))())
    ((("$"). ("??"))())
    ((("%"). ("??"))())
    ((("&"). ("??"))())
    ((("'"). ("??"))())
    ((("("). ("??"))())
    (((")"). ("??"))())
    ((("~"). ("??"))())
    ((("Z"). ("??"))())
    ((("y"). ("??"))())
    ((("3"). ("??"))())
    ((("e"). ("??"))())
    ((("4"). ("??"))())
    ((("5"). ("??"))())
    ((("6"). ("??"))())
    ((("t"). ("??"))())
    ((("g"). ("??"))())
    ((("h"). ("??"))())
    (((":"). ("??"))())
    ((("b"). ("??"))())
    ((("x"). ("??"))())
    ((("d"). ("??"))())
    ((("r"). ("??"))())
    ((("p"). ("??"))())
    ((("c"). ("??"))())
    ((("q"). ("??"))())
    ((("a"). ("??"))())
    ((("z"). ("??"))())
    ((("w"). ("??"))())
    ((("s"). ("??"))())
    ((("u"). ("??"))())
    ((("i"). ("??"))())
    ((("1"). ("??"))())
    (((","). ("??"))())
    ((("k"). ("??"))())
    ((("f"). ("??"))())
    ((("v"). ("??"))())
    ((("2"). ("??"))())
    ((("^"). ("??"))())
    ((("-"). ("??"))())
    ((("j"). ("??"))())
    ((("n"). ("??"))())
    ((("]"). ("??"))())
    ((("/"). ("??"))())
    ((("m"). ("??"))())
    ((("7"). ("??"))())
    ((("8"). ("??"))())
    ((("9"). ("??"))())
    ((("o"). ("??"))())
    ((("l"). ("??"))())
    ((("."). ("??"))())
    (((";"). ("??"))())
    ((("0"). ("??"))())
    ((("|"). ("??"))())
    ((("T"). ("??"))())
    ((("G"). ("??"))())
    ((("H"). ("??"))())
    ((("*"). ("??"))())
    ((("B"). ("??"))())
    ((("X"). ("??"))())
    ((("D"). ("??"))())
    ((("R"). ("??"))())
    ((("P"). ("??"))())
    ((("C"). ("??"))())
    ((("Q"). ("??"))())
    ((("A"). ("??"))())
    ((("W"). ("??"))())
    ((("S"). ("??"))())
    ((("U"). ("??"))())
    ((("I"). ("??"))())
    ((("!"). ("??"))())
    ((("K"). ("??"))())
    ((("F"). ("??"))())
    ((("V"). ("??"))())
    ((("\""). ("??"))())
    ((("="). ("??"))())
    ((("J"). ("??"))())
    ((("N"). ("??"))())
    ((("M"). ("??"))())
    ((("O"). ("??"))())
    ((("L"). ("??"))())
    ((("+"). ("??"))())
    ((("_"). ("??"))())
    ((("Y"). ("??"))())
    ((("\\"). ("??"))())
    ((("yen"). ("??"))())

    ((("kana-a"). ("??"))())
    ((("kana-i"). ("??"))())
    ((("kana-u"). ("??"))())
    ((("kana-e"). ("??"))())
    ((("kana-o"). ("??"))())
    ((("kana-ya"). ("??"))())
    ((("kana-yu"). ("??"))())
    ((("kana-yo"). ("??"))())
    ((("kana-WO"). ("??"))())
    ((("kana-tsu"). ("??"))())
    ((("kana-N"). ("??"))())
    ((("kana-A"). ("??"))())
    ((("kana-I"). ("??"))())
    ((("kana-U"). ("??"))())
    ((("kana-E"). ("??"))())
    ((("kana-O"). ("??"))())
    ((("kana-KA"). ("??"))())
    ((("kana-KI"). ("??"))())
    ((("kana-KU"). ("??"))())
    ((("kana-KE"). ("??"))())
    ((("kana-KO"). ("??"))())
    ((("kana-SA"). ("??"))())
    ((("kana-SHI"). ("??"))())
    ((("kana-SU"). ("??"))())
    ((("kana-SE"). ("??"))())
    ((("kana-SO"). ("??"))())
    ((("kana-TA"). ("??"))())
    ((("kana-CHI"). ("??"))())
    ((("kana-TSU"). ("??"))())
    ((("kana-TE"). ("??"))())
    ((("kana-TO"). ("??"))())
    ((("kana-NA"). ("??"))())
    ((("kana-NI"). ("??"))())
    ((("kana-NU"). ("??"))())
    ((("kana-NE"). ("??"))())
    ((("kana-NO"). ("??"))())
    ((("kana-HA"). ("??"))())
    ((("kana-HI"). ("??"))())
    ((("kana-FU"). ("??"))())
    ((("kana-HE"). ("??"))())
    ((("kana-HO"). ("??"))())
    ((("kana-MA"). ("??"))())
    ((("kana-MI"). ("??"))())
    ((("kana-MU"). ("??"))())
    ((("kana-ME"). ("??"))())
    ((("kana-MO"). ("??"))())
    ((("kana-YA"). ("??"))())
    ((("kana-YU"). ("??"))())
    ((("kana-YO"). ("??"))())
    ((("kana-RA"). ("??"))())
    ((("kana-RI"). ("??"))())
    ((("kana-RU"). ("??"))())
    ((("kana-RE"). ("??"))())
    ((("kana-RO"). ("??"))())
    ((("kana-WA"). ("??"))())
    ((("kana-prolonged-sound"). ("??"))())

    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("????"))
    ((("??" "@"). ())("??"))
    ((("??" "@"). ())("?Î?"))
    ((("??" "@"). ())("?Ď?"))
    ((("??" "@"). ())("?ʎ?"))
    ((("??" "@"). ())("?ˎ?"))
    ((("??" "@"). ())("?̎?"))
    ((("??" "@"). ())("?͎?"))
    ((("??" "@"). ())("?Ύ?"))
    ((("??" "["). ())("?ʎ?"))
    ((("??" "["). ())("?ˎ?"))
    ((("??" "["). ())("?̎?"))
    ((("??" "["). ())("?͎?"))
    ((("??" "["). ())("?Ύ?"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("????"))
    ((("??" "`"). ())("??"))
    ((("??" "`"). ())("?Î?"))
    ((("??" "`"). ())("?Ď?"))
    ((("??" "`"). ())("?ʎ?"))
    ((("??" "`"). ())("?ˎ?"))
    ((("??" "`"). ())("?̎?"))
    ((("??" "`"). ())("?͎?"))
    ((("??" "`"). ())("?Ύ?"))

    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("????"))
    ((("??" "kana-voiced-sound"). ())("??"))
    ((("??" "kana-voiced-sound"). ())("?Î?"))
    ((("??" "kana-voiced-sound"). ())("?Ď?"))
    ((("??" "kana-voiced-sound"). ())("?ʎ?"))
    ((("??" "kana-voiced-sound"). ())("?ˎ?"))
    ((("??" "kana-voiced-sound"). ())("?̎?"))
    ((("??" "kana-voiced-sound"). ())("?͎?"))
    ((("??" "kana-voiced-sound"). ())("?Ύ?"))
    ((("??" "kana-semivoiced-sound"). ())("?ʎ?"))
    ((("??" "kana-semivoiced-sound"). ())("?ˎ?"))
    ((("??" "kana-semivoiced-sound"). ())("?̎?"))
    ((("??" "kana-semivoiced-sound"). ())("?͎?"))
    ((("??" "kana-semivoiced-sound"). ())("?Ύ?"))
 
    (((">"). ("??"))())
    ((("<"). ("??"))())
    ((("?"). ("??"))())
    ((("@"). ("??"))())
    ((("["). ("??"))())
    ((("{"). ("??"))())
    ((("}"). ("??"))())
    ((("`"). ("??"))())

    ((("kana-fullstop"). ("??"))())
    ((("kana-comma"). ("??"))())
    ((("kana-conjunctive"). ("??"))())
    ((("kana-voiced-sound"). ("??"))())
    ((("kana-semivoiced-sound"). ("??"))())
    ((("kana-opening-bracket"). ("??"))())
    ((("kana-closing-bracket"). ("??"))())
 
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ((("??"). ())("??"))
    ))
