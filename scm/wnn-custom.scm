;;; wnn-custom.scm: Customization variables for wnn.scm
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

(require "i18n.scm")


(define wnn-im-name-label (N_ "Wnn"))
(define wnn-im-short-desc (N_ "A multi-segment kana-kanji conversion engine"))

(define-custom-group 'wnn
                     wnn-im-name-label
                     wnn-im-short-desc)

(define-custom-group 'wnnserver
		     (N_ "Wnn server")
		     (N_ "long description will be here."))

(define-custom-group 'wnn-advanced
		     (N_ "Wnn (advanced)")
		     (N_ "long description will be here."))

(define-custom-group 'wnn-prediction
		     (N_ "Prediction")
		     (N_ "long description will be here."))

;;
;; segment separator
;;

(define-custom 'wnn-show-segment-separator? #f
  '(wnn segment-sep)
  '(boolean)
  (N_ "Show segment separator")
  (N_ "long description will be here."))

(define-custom 'wnn-segment-separator "|"
  '(wnn segment-sep)
  '(string ".*")
  (N_ "Segment separator")
  (N_ "long description will be here."))

(custom-add-hook 'wnn-segment-separator
		 'custom-activity-hooks
		 (lambda ()
		   wnn-show-segment-separator?))

;;
;; candidate window
;;

(define-custom 'wnn-use-candidate-window? #t
  '(wnn candwin)
  '(boolean)
  (N_ "Use candidate window")
  (N_ "long description will be here."))

(define-custom 'wnn-candidate-op-count 1
  '(wnn candwin)
  '(integer 0 99)
  (N_ "Conversion key press count to show candidate window")
  (N_ "long description will be here."))

(define-custom 'wnn-nr-candidate-max 10
  '(wnn candwin)
  '(integer 1 20)
  (N_ "Number of candidates in candidate window at a time")
  (N_ "long description will be here."))

(define-custom 'wnn-select-candidate-by-numeral-key? #f
  '(wnn candwin)
  '(boolean)
  (N_ "Select candidate by numeral keys")
  (N_ "long description will be here."))

;; activity dependency
(custom-add-hook 'wnn-candidate-op-count
		 'custom-activity-hooks
		 (lambda ()
		   wnn-use-candidate-window?))

(custom-add-hook 'wnn-nr-candidate-max
		 'custom-activity-hooks
		 (lambda ()
		   wnn-use-candidate-window?))

(custom-add-hook 'wnn-select-candidate-by-numeral-key?
		 'custom-activity-hooks
		 (lambda ()
		   wnn-use-candidate-window?))

;;
;; toolbar
;;

;; Can't be unified with action definitions in wnn.scm until uim
;; 0.4.6.
(define wnn-input-mode-indication-alist
  (list
   (list 'action_wnn_direct
	 'ja_direct
	 "-"
	 (N_ "Direct input")
	 (N_ "Direct input mode"))
   (list 'action_wnn_hiragana
	 'ja_hiragana
	 "??"
	 (N_ "Hiragana")
	 (N_ "Hiragana input mode"))
   (list 'action_wnn_katakana
	 'ja_katakana
	 "??"
	 (N_ "Katakana")
	 (N_ "Katakana input mode"))
   (list 'action_wnn_halfkana
	 'ja_halfkana
	 "??"
	 (N_ "Halfwidth Katakana")
	 (N_ "Halfwidth Katakana input mode"))
   (list 'action_wnn_halfwidth_alnum
	 'ja_halfwidth_alnum
	 "a"
	 (N_ "Halfwidth Alphanumeric")
	 (N_ "Halfwidth Alphanumeric input mode"))

   (list 'action_wnn_fullwidth_alnum
	 'ja_fullwidth_alnum
	 "??"
	 (N_ "Fullwidth Alphanumeric")
	 (N_ "Fullwidth Alphanumeric input mode"))))

(define wnn-kana-input-method-indication-alist
  (list
   (list 'action_wnn_roma
	 'ja_romaji
	 "??"
	 (N_ "Romaji")
	 (N_ "Romaji input mode"))
   (list 'action_wnn_kana
	 'ja_kana
	 "??"
	 (N_ "Kana")
	 (N_ "Kana input mode"))
   (list 'action_wnn_azik
	 'ja_azik
	 "??"
	 (N_ "AZIK")
	 (N_ "AZIK extended romaji input mode"))
   (list 'action_wnn_act
	 'ja_act
	 "??"
	 (N_ "ACT")
	 (N_ "ACT extended romaji input mode"))
   (list 'action_wnn_kzik
	 'ja_kzik
	 "??"
	 (N_ "KZIK")
	 (N_ "KZIK extended romaji input mode"))))

;;; Buttons

(define-custom 'wnn-widgets '(widget_wnn_input_mode
				widget_wnn_kana_input_method)
  '(wnn toolbar-widget)
  (list 'ordered-list
	(list 'widget_wnn_input_mode
	      (N_ "Input mode")
	      (N_ "Input mode"))
	(list 'widget_wnn_kana_input_method
	      (N_ "Kana input method")
	      (N_ "Kana input method")))
  (N_ "Enabled toolbar buttons")
  (N_ "long description will be here."))

;; dynamic reconfiguration
;; wnn-configure-widgets is not defined at this point. So wrapping
;; into lambda.
(custom-add-hook 'wnn-widgets
		 'custom-set-hooks
		 (lambda ()
		   (wnn-configure-widgets)))


;;; Input mode

(define-custom 'default-widget_wnn_input_mode 'action_wnn_direct
  '(wnn toolbar-widget)
  (cons 'choice
	(map indication-alist-entry-extract-choice
	     wnn-input-mode-indication-alist))
  (N_ "Default input mode")
  (N_ "long description will be here."))

(define-custom 'wnn-input-mode-actions
               (map car wnn-input-mode-indication-alist)
  '(wnn toolbar-widget)
  (cons 'ordered-list
	(map indication-alist-entry-extract-choice
	     wnn-input-mode-indication-alist))
  (N_ "Input mode menu items")
  (N_ "long description will be here."))

;; value dependency
(if custom-full-featured?
    (custom-add-hook 'wnn-input-mode-actions
		     'custom-set-hooks
		     (lambda ()
		       (custom-choice-range-reflect-olist-val
			'default-widget_wnn_input_mode
			'wnn-input-mode-actions
			wnn-input-mode-indication-alist))))

;; activity dependency
(custom-add-hook 'default-widget_wnn_input_mode
		 'custom-activity-hooks
		 (lambda ()
		   (memq 'widget_wnn_input_mode wnn-widgets)))

(custom-add-hook 'wnn-input-mode-actions
		 'custom-activity-hooks
		 (lambda ()
		   (memq 'widget_wnn_input_mode wnn-widgets)))

;; dynamic reconfiguration
(custom-add-hook 'default-widget_wnn_input_mode
		 'custom-set-hooks
		 (lambda ()
		   (wnn-configure-widgets)))

(custom-add-hook 'wnn-input-mode-actions
		 'custom-set-hooks
		 (lambda ()
		   (wnn-configure-widgets)))

;;; Kana input method

(define-custom 'default-widget_wnn_kana_input_method 'action_wnn_roma
  '(wnn toolbar-widget)
  (cons 'choice
	(map indication-alist-entry-extract-choice
	     wnn-kana-input-method-indication-alist))
  (N_ "Default kana input method")
  (N_ "long description will be here."))

(define-custom 'wnn-kana-input-method-actions
               (map car wnn-kana-input-method-indication-alist)
  '(wnn toolbar-widget)
  (cons 'ordered-list
	(map indication-alist-entry-extract-choice
	     wnn-kana-input-method-indication-alist))
  (N_ "Kana input method menu items")
  (N_ "long description will be here."))

;; value dependency
(if custom-full-featured?
    (custom-add-hook 'wnn-kana-input-method-actions
		     'custom-set-hooks
		     (lambda ()
		       (custom-choice-range-reflect-olist-val
			'default-widget_wnn_kana_input_method
			'wnn-kana-input-method-actions
			wnn-kana-input-method-indication-alist))))

;; activity dependency
(custom-add-hook 'default-widget_wnn_kana_input_method
		 'custom-activity-hooks
		 (lambda ()
		   (memq 'widget_wnn_kana_input_method wnn-widgets)))

(custom-add-hook 'wnn-kana-input-method-actions
		 'custom-activity-hooks
		 (lambda ()
		   (memq 'widget_wnn_kana_input_method wnn-widgets)))

;; dynamic reconfiguration
(custom-add-hook 'default-widget_wnn_kana_input_method
		 'custom-set-hooks
		 (lambda ()
		   (wnn-configure-widgets)))

(custom-add-hook 'wnn-kana-input-method-actions
		 'custom-set-hooks
		 (lambda ()
		   (wnn-configure-widgets)))


;;
;; wnn-server-name
;;

(define-custom 'wnn-use-remote-server? #f
  '(wnn-advanced wnnserver)
  '(boolean)
  (N_ "Use remote Wnn server")
  (N_ "long description will be here."))


(define-custom 'wnn-server-name "localhost"
  '(wnn-advanced wnnserver)
  '(string ".*")
  (N_ "Wnn server name")
  (N_ "long description will be here."))

(custom-add-hook 'wnn-server-name
                 'custom-activity-hooks
                 (lambda ()
                   wnn-use-remote-server?))

(define-custom 'wnn-rcfile ""
  '(wnn-advanced wnnserver)
  '(pathname regular-file)
  (N_ "Wnn resource file")
  (N_ "long description will be here."))

(define-custom 'wnn-use-with-vi? #f
  '(wnn-advanced special-op)
  '(boolean)
  (N_ "Enable vi-cooperative mode")
  (N_ "long description will be here."))

(define-custom 'wnn-use-mode-transition-keys-in-off-mode? #f
  '(wnn-advanced mode-transition)
  '(boolean)
  (N_ "Enable input mode transition keys in direct (off state) input mode")
  (N_ "long description will be here."))

;; prediction
(define-custom 'wnn-use-prediction? #f
  '(wnn-advanced wnn-prediction)
  '(boolean)
  (N_ "Enable input prediction")
  (N_ "long description will be here."))

(define-custom 'wnn-select-prediction-by-numeral-key? #f
  '(wnn-advanced wnn-prediction)
  '(boolean)
  (N_ "Select prediction candidate by numeral keys")
  (N_ "long description will be here."))

(define-custom 'wnn-use-implicit-commit-prediction? #t
  '(wnn-advanced wnn-prediction)
  '(boolean)
  (N_ "Show selected prediction candidate in preedit area")
  (N_ "long description will be here."))

(define-custom 'wnn-prediction-cache-words 256
  '(wnn-advanced wnn-prediction)
  '(integer 1 65535)
  (N_ "Number of cache of prediction candidates")
  (N_ "long description will be here."))

(define-custom 'wnn-prediction-start-char-count 2
  '(wnn-advanced wnn-prediction)
  '(integer 1 65535)
  (N_ "Character count to start input prediction")
  (N_ "long description will be here."))

(custom-add-hook 'wnn-use-candidate-window?
                 'custom-get-hooks
                 (lambda ()
                   (if (not wnn-use-candidate-window?)
                       (set! wnn-use-prediction? #f))))

(custom-add-hook 'wnn-use-prediction?
                 'custom-activity-hooks
                 (lambda ()
                   wnn-use-candidate-window?))

(custom-add-hook 'wnn-select-prediction-by-numeral-key?
                 'custom-activity-hooks
                 (lambda ()
                   wnn-use-prediction?))

(custom-add-hook 'wnn-use-implicit-commit-prediction?
                 'custom-activity-hooks
                 (lambda ()
                   wnn-use-prediction?))

(custom-add-hook 'wnn-prediction-cache-words
                 'custom-activity-hooks
                 (lambda ()
                   wnn-use-prediction?))

(custom-add-hook 'wnn-prediction-start-char-count
                 'custom-activity-hooks
                 (lambda ()
                   wnn-use-prediction?))
