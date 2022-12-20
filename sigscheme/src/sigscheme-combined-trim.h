/* This is an auto-generated file. Don't edit directly. */

/* alloc.c */

/* storage.c */
#undef SCM_CONSTANT_BIND_SUBSTANCE
#undef SCM_CONS_INIT
#undef SCM_IMMUTABLE_CONS_INIT
#undef SCM_CLOSURE_INIT
#undef SCM_CHAR_INIT
#undef SCM_INT_INIT
#undef SCM_SYMBOL_INIT
#undef SCM_STRING_INIT
#undef SCM_MUTABLE_STRING_INIT
#undef SCM_IMMUTABLE_STRING_INIT
#undef SCM_FUNC_INIT
#undef SCM_VECTOR_INIT
#undef SCM_MUTABLE_VECTOR_INIT
#undef SCM_IMMUTABLE_VECTOR_INIT
#undef SCM_PORT_INIT
#undef SCM_CONTINUATION_INIT
#undef SCM_C_POINTER_INIT
#undef SCM_C_FUNCPOINTER_INIT
#undef SCM_VALUEPACKET_INIT
#undef SCM_HMACRO_INIT
#undef SCM_FARSYMBOL_INIT
#undef SCM_SUBPAT_INIT
#undef static
#undef l_null_cell
#undef l_true_cell
#undef l_false_cell
#undef l_eof_cell
#undef l_unbound_cell
#undef l_undef_cell

/* storage-gc.c */
#undef SCMOBJ_ALIGNEDP
#undef SCM_BEGIN_GC_SUBCONTEXT
#undef SCM_END_GC_SUBCONTEXT
#undef static
#undef l_heap_size
#undef l_heap_alloc_threshold
#undef l_n_heaps
#undef l_n_heaps_max
#undef l_heaps
#undef l_heaps_lowest
#undef l_heaps_highest
#undef l_freelist
#undef l_protected_vars
#undef l_protected_vars_size
#undef l_n_empty_protected_vars
#undef l_gcroots_ctx
#undef l_gcing
#undef l_allocating

/* error.c */
#undef SCM_BACKTRACE_HEADER
#undef SCM_BACKTRACE_SEP
#undef NO_ERR_OBJ
#undef UNBOUNDP
#undef static
#undef l_debug_mask
#undef l_srfi34_is_provided
#undef l_error_looped
#undef l_fatal_error_looped
#undef l_cb_fatal_error
#undef l_err_obj_tag

/* symbol.c */

/* env.c */
#undef TRUSTED_ENVP

/* eval.c */
#undef SCM_ERRMSG_NON_R5RS_ENV

/* syntax.c */
#undef ERRMSG_CLAUSE_REQUIRED
#undef ERRMSG_EXPRESSION_REQUIRED
#undef ERRMSG_INVALID_BINDINGS
#undef ERRMSG_INVALID_BINDING
#undef ERRMSG_SYNTAX_AS_VALUE
#undef ERRMSG_DUPLICATE_VARNAME
#undef ERRMSG_BAD_DEFINE_FORM
#undef ERRMSG_BAD_DEFINE_PLACEMENT
#undef FORBID_TOPLEVEL_DEFINITIONS
#undef CHECK_VALID_BINDEE
#undef static
#undef l_sym_else
#undef l_sym_yields
#undef l_sym_define
#undef l_sym_begin
#undef l_syn_lambda

/* procedure.c */
#undef ERRMSG_UNEVEN_MAP_ARGS
#undef scm_p_eqvp

/* list.c */
#undef MEMBER_BODY
#undef ASSOC_BODY

/* sigschemeinternal.h */
#undef SYM_QUOTE
#undef SYM_QUASIQUOTE
#undef SYM_UNQUOTE
#undef SYM_UNQUOTE_SPLICING
#undef SYM_ELLIPSIS
#undef EQ
#undef NULLP
#undef FALSEP
#undef TRUEP
#undef EOFP
#undef CAR
#undef CDR
#undef SET_CAR
#undef SET_CDR
#undef CAAR
#undef CADR
#undef CDAR
#undef CDDR
#undef CONS
#undef IMMUTABLE_CONS
#undef LIST_1
#undef LIST_2
#undef LIST_3
#undef LIST_4
#undef LIST_5
#undef DEREF
#undef SET
#undef REF_CAR
#undef REF_CDR
#undef REF_OFF_HEAP
#undef EVAL
#undef MAKE_BOOL
#undef MAKE_INT
#undef MAKE_CONS
#undef MAKE_IMMUTABLE_CONS
#undef MAKE_SYMBOL
#undef MAKE_CHAR
#undef MAKE_STRING
#undef MAKE_STRING_COPYING
#undef MAKE_IMMUTABLE_STRING
#undef MAKE_IMMUTABLE_STRING_COPYING
#undef CONST_STRING
#undef STRLEN_UNKNOWN
#undef MAKE_FUNC
#undef MAKE_CLOSURE
#undef MAKE_VECTOR
#undef MAKE_IMMUTABLE_VECTOR
#undef MAKE_PORT
#undef MAKE_CONTINUATION
#undef MAKE_C_POINTER
#undef MAKE_C_FUNCPOINTER
#undef MAKE_VALUEPACKET
#undef MAKE_HMACRO
#undef MAKE_FARSYMBOL
#undef MAKE_SUBPAT
#undef NUMBERP
#undef INTP
#undef CONSP
#undef SYMBOLP
#undef CHARP
#undef STRINGP
#undef FUNCP
#undef SYNTAXP
#undef CLOSUREP
#undef SYNTACTIC_CLOSUREP
#undef PROCEDUREP
#undef SYNTACTIC_OBJECTP
#undef VECTORP
#undef PORTP
#undef CONTINUATIONP
#undef NULLVALUESP
#undef VALUEPACKETP
#undef HMACROP
#undef FARSYMBOLP
#undef SUBPATP
#undef FREECELLP
#undef C_POINTERP
#undef C_FUNCPOINTERP
#undef ENVP
#undef VALID_ENVP
#undef ERROBJP
#undef IDENTIFIERP
#undef LISTP
#undef LIST_1_P
#undef LIST_2_P
#undef LIST_3_P
#undef LIST_4_P
#undef LIST_5_P
#undef PROPER_LISTP
#undef DOTTED_LISTP
#undef CIRCULAR_LISTP
#undef CDBG
#undef DBG
#undef ENSURE_ALLOCATED
#undef ENSURE_PROPER_LIST_TERMINATION
#undef CHECK_PROPER_LIST_TERMINATION
#undef SCM_ERR_HEADER
#undef ERRMSG_FIXNUM_OVERFLOW
#undef ERRMSG_UNHANDLED_EXCEPTION
#undef SCM_ERRMSG_IMPROPER_ARGS
#undef SCM_ERRMSG_NULL_IN_STRING
#undef ERRMSG_UNSUPPORTED_ENCODING
#undef ERRMSG_CODEC_SW_NOT_SUPPORTED
#undef SCM_INTERACTION_ENV_INDEFINABLE
#undef SCM_NESTED_CONTINUATION_ONLY
#undef INVALID_CONTINUATION_OPAQUE
#undef MAKE_TRACE_FRAME
#undef TRACE_FRAME_OBJ
#undef TRACE_FRAME_ENV
#undef SCM_VALUEPACKET_VALUES
#undef SCM_NULLVALUESP
#undef SCM_VALUECONS_CAR
#undef SCM_VALUECONS_CDR
#undef SCM_VALUEPACKET_SET_VALUES
#undef SCM_AS_FREECELL
#undef SCM_FREECELLP
#undef SCM_FREECELL_NEXT
#undef SCM_FREECELL_FREESLOT
#undef SCM_FREECELL_SET_NEXT
#undef SCM_FREECELL_SET_FREESLOT
#undef SCM_FREECELL_CLEAR_FREESLOT
#undef EQVP
#undef EQUALP
#undef STRING_EQUALP
#undef SCM_LISTLEN_ENCODE_DOTTED
#undef SCM_LISTLEN_ENCODE_CIRCULAR
#undef SCM_LISTLEN_ENCODE_ERROR
#undef SCM_MANGLE
#undef VALIDP
#undef DECLARE_FUNCTION
#undef DECLARE_INTERNAL_FUNCTION
#undef PLAIN_ERR
#undef ERR
#undef scm_err_funcname
#undef ERR_OBJ
#undef SCM_ENSURE_PROPER_LIST_TERMINATION
#undef SCM_CHECK_PROPER_LIST_TERMINATION
#undef ENSURE_NO_MORE_ARG
#undef ENSURE_PROPER_ARG_LIST
#undef NO_MORE_ARG
#undef ASSERT_NO_MORE_ARG
#undef ASSERT_PROPER_ARG_LIST
#undef POP
#undef SAFE_POP
#undef MUST_POP_ARG
#undef FOR_EACH_WHILE
#undef FOR_EACH
#undef FOR_EACH_PAIR
#undef FOR_EACH_BUTLAST
#undef ENSURE_TYPE
#undef ENSURE_INT
#undef ENSURE_CONS
#undef ENSURE_SYMBOL
#undef ENSURE_CHAR
#undef ENSURE_STRING
#undef ENSURE_FUNC
#undef ENSURE_CLOSURE
#undef ENSURE_VECTOR
#undef ENSURE_PORT
#undef ENSURE_CONTINUATION
#undef ENSURE_PROCEDURE
#undef ENSURE_ENV
#undef ENSURE_VALID_ENV
#undef ENSURE_ERROBJ
#undef ENSURE_LIST
#undef ENSURE_IDENTIFIER
#undef ENSURE_MUTABLE_CONS
#undef ENSURE_MUTABLE_STRING
#undef ENSURE_MUTABLE_VECTOR
#undef ENSURE_STATEFUL_CODEC
#undef ENSURE_STATELESS_CODEC
#undef CHECK_VALID_EVALED_VALUE
#undef INT_VALID_VALUEP
#undef INT_OUT_OF_RANGEP
#undef ICHAR_ASCIIP
#undef ICHAR_SINGLEBYTEP
#undef ICHAR_VALID_UNICODEP
#undef ICHAR_CONTROLP
#undef ICHAR_WHITESPACEP
#undef ICHAR_NUMERICP
#undef ICHAR_HEXA_NUMERICP
#undef ICHAR_ALPHABETICP
#undef ICHAR_UPPER_CASEP
#undef ICHAR_LOWER_CASEP
#undef ICHAR_DOWNCASE
#undef ICHAR_UPCASE
#undef ICHAR_FOLDCASE
#undef ScmLBuf
#undef LBUF_BUF
#undef LBUF_END
#undef LBUF_SIZE
#undef LBUF_INIT_SIZE
#undef LBUF_EXT_CNT
#undef LBUF_INIT
#undef LBUF_FREE
#undef LBUF_ALLOC
#undef LBUF_REALLOC
#undef LBUF_EXTEND
#undef scm_identifier_codec
#undef scm_values_applier
#undef scm_in
#undef scm_out
#undef scm_err
#undef scm_write_ss_func
#undef scm_null_values
#undef scm_symbol_hash
#undef scm_symbol_hash_size
#undef strcasecmp
#undef scm_trace_stack
#undef scm_s_body

/* module.c */
#undef static
#undef l_features
#undef l_provided_modules

/* sigscheme.c */
#undef scm_p_call_with_current_continuation
#undef scm_p_dynamic_wind
#undef static
#undef l_scm_initialized

/* continuation.c */
#undef JMP_BUF
#undef SETJMP
#undef LONGJMP
#undef CONTINUATION_FRAME
#undef CONTINUATION_SET_FRAME
#undef static
#undef l_current_dynamic_extent
#undef l_continuation_stack
#undef l_trace_stack
#undef MAKE_DYNEXT_FRAME
#undef DYNEXT_FRAME_BEFORE
#undef DYNEXT_FRAME_AFTER

/* scmport-file.c */
#undef OK

/* scmport-basechar.c */

/* encoding.c */
#undef utf8_codec
#undef euccn_codec
#undef eucjp_codec
#undef euckr_codec
#undef sjis_codec
#undef unibyte_codec
#undef ENTER
#undef RETURN
#undef RETURN_ERROR
#undef RETURN_INCOMPLETE
#undef SAVE_STATE
#undef EXPECT_SIZE
#undef IN_CL
#undef IN_CR
#undef IN_GL94
#undef IN_GL96
#undef IN_GR94
#undef IN_GR96
#undef IS_ASCII
#undef IS_GR_SPC_OR_DEL
#undef CHAR_BITS
#undef BYTE_MASK
#undef IS_1BYTE
#undef IS_2BYTES
#undef IS_3BYTES
#undef ESC
#undef SO
#undef SI
#undef SS2
#undef SS3
#undef IN_OCT_BMP
#undef IN_BMP
#undef IN_SMP
#undef MASK
#undef LEN_CODE
#undef IS_LEN
#undef IS_TRAILING
#undef LEN_CODE_BITS
#undef TRAILING_CODE_BITS
#undef TRAILING_VAL_BITS
#undef LEADING_VAL_BITS
#undef LEADING_VAL
#undef TRAILING_VAL
#undef IS_KANA
#undef IS_LEAD
#undef IS_TRAIL

/* scmport-mbchar.c */
#undef HANDLE_MBC_START
#undef SCM_MBCPORT_CLEAR_STATE
#undef static
#undef l_ScmMultiByteCharPort_vtbl

/* scmport-sbchar.c */
#undef static
#undef l_sbc_codec
#undef l_ScmSingleByteCharPort_vtbl

/* format.c */
#undef ERRMSG_INVALID_ESCSEQ
#undef MSG_SRFI48_DIRECTIVE_HELP
#undef MSG_SSCM_DIRECTIVE_HELP
#undef NEWLINE_CHAR
#undef FORMAT_STR_INIT
#undef FORMAT_STR_POS
#undef FORMAT_STR_ENDP
#undef FORMAT_STR_READ
#undef FORMAT_STR_PEEK
#undef FORMAT_STR_SKIP_CHAR
#undef POP_FORMAT_ARG
#undef static
#undef l_sym_pretty_print

/* qquote.c */
#undef ERRMSG_BAD_SPLICE_LIST
#undef TR_BOOL_MSG_P
#undef TRL_INIT
#undef TRL_GET_ELM
#undef TRL_NEXT
#undef TRL_ENDP
#undef TRL_GET_SUBLS
#undef TRL_SET_SUBLS
#undef TRL_EXTRACT
#undef TRL_CALL
#undef TRL_EXECUTE
#undef TRV_INIT
#undef TRV_GET_ELM
#undef TRV_NEXT
#undef TRV_GET_INDEX
#undef TRV_GET_VEC
#undef TRV_ENDP
#undef TRV_EXTRACT
#undef TRV_EXECUTE
#undef TRV_CALL
#undef TR_CALL
#undef TR_EXECUTE
#undef TR_GET_ELM
#undef TR_NEXT
#undef TR_ENDP
#undef TR_EXTRACT
#undef RETURN_OBJECT
#undef RETURN_BOOLEAN
#undef REPLACED_INDEX
#undef SPLICED_INDEX

/* macro.c */
#undef static
#undef l_debug_mode
#undef SYM_SYNTAX_RULES
#undef ELLIPSISP
#undef MAKE_PVAR
#undef PVAR_INDEX
#undef PVARP
#undef MAKE_REPPAT
#undef REPPAT_PAT
#undef REPPAT_PVCOUNT
#undef REPPATP
#undef DBG_PRINT
#undef INIT_DBG
#undef DEFINE
#undef MATCH_REC
#undef MISMATCH
#undef DEFAULT_INDEX_BUF_SIZE
#undef RECURSE
#undef RECURSE_ALWAYS_APPEND
#undef UPTO_LAST_PAIR

/* legacy-macro.c */

/* promise.c */
#undef PROMISE_FORCEDP
#undef static
#undef l_tag_unforced

/* number.c */
#undef ERRMSG_DIV_BY_ZERO
#undef ERRMSG_REQ_1_ARG
#undef COMPARATOR_BODY

/* number-io.c */
#undef VALID_RADIXP

/* char.c */
#undef CHAR_CMP_BODY
#undef CHAR_CI_CMP_BODY

/* string.c */

/* string-procedure.c */
#undef STRING_CMP
#undef STRING_CI_CMP

/* vector.c */

/* port.c */
#undef ERRMSG_CANNOT_OPEN_FILE
#undef scm_p_read_char
#undef scm_p_peek_char
#undef scm_p_char_readyp
#undef scm_p_write_char

/* read.c */
#undef OK
#undef TOKEN_BUF_EXCEEDED
#undef CHAR_LITERAL_LEN_MAX
#undef INT_LITERAL_LEN_MAX
#undef DISCARD_LOOKAHEAD
#undef ICHAR_ASCII_CLASS
#undef ICHAR_CLASS

/* write.c */
#undef STRINGP
#undef SCM_STRING_LEN
#undef VECTORP
#undef INTERESTINGP
#undef OCCUPIED
#undef HASH_EMPTY
#undef DEFINING_DATUM
#undef NONDEFINING_DATUM
#undef HASH_INSERT
#undef HASH_FIND
#undef static
#undef l_write_ss_ctx

/* load.c */
#undef ABSOLUTE_PATHP
#undef PATH_SEPARATOR
#undef SCRIPT_PRELUDE_MAXLEN
#undef SCRIPT_PRELUDE_DELIM
#undef static
#undef l_scm_lib_path
#undef l_scm_system_load_path

/* deep-cadrs.c */

/* module-sscm-ext.c */
#undef ERRMSG_INVALID_BINDINGS
#undef ERRMSG_INVALID_BINDING

/* module-siod.c */
#undef SCM_DBG_SIOD_V0
#undef SCM_DBG_SIOD_V1
#undef SCM_DBG_SIOD_V2
#undef SCM_DBG_SIOD_V3
#undef SCM_DBG_SIOD_V4
#undef SCM_DBG_SIOD_V5
#undef static
#undef l_sscm_verbose_level
#undef l_null_port
#undef l_saved_output_port
#undef l_saved_error_port

/* scmport-null.c */

/* module-srfi1.c */

/* module-srfi2.c */

/* module-srfi6.c */

/* scmport-str.c */

/* module-srfi8.c */

/* module-srfi9.c */
#undef ERRMSG_MISPLACED_RECORD_DEFINITION
#undef SYMBOL_VALUE
#undef static
#undef l_proc_car
#undef l_proc_make_record_type
#undef l_proc_record_constructor
#undef l_proc_record_predicate
#undef l_proc_record_accessor
#undef l_proc_record_modifier

/* module-srfi23.c */

/* module-srfi28.c */

/* module-srfi34.c */
#undef USE_WITH_SIGSCHEME_FATAL_ERROR
#undef ERRMSG_HANDLER_RETURNED
#undef ERRMSG_FALLBACK_EXHAUSTED
#undef DECLARE_PRIVATE_FUNCTION
#undef N_GLOBAL_SCMOBJ
#undef static
#undef l_current_exception_handlers
#undef l_errmsg_unhandled_exception
#undef l_errmsg_handler_returned
#undef l_errmsg_fallback_exhausted
#undef l_sym_error
#undef l_sym_raise
#undef l_sym_lex_env
#undef l_sym_cond_catch
#undef l_sym_body
#undef l_sym_condition
#undef l_sym_guard_k
#undef l_sym_handler_k
#undef l_syn_raw_quote
#undef l_syn_apply
#undef l_proc_values
#undef l_syn_set_cur_handlers
#undef l_proc_fallback_handler
#undef l_proc_with_exception_handlers
#undef l_syn_guard_internal
#undef l_syn_guard_handler
#undef l_syn_guard_handler_body
#undef l_syn_guard_body

/* module-srfi38.c */

/* module-srfi43.c */
#undef QUOTE
#undef static
#undef l_sym_vector_parse_start_plus_end
#undef l_sym_check_type
#undef l_sym_vectorp

/* module-srfi48.c */

/* module-srfi55.c */
#undef static
#undef l_sym_require_extension

/* module-srfi60.c */
#undef BITWISE_OPERATION_BODY

/* gcroots/gcroots.h */
#undef _GCROOTS_H
#undef GCROOTS_VERSION_MAJOR
#undef GCROOTS_VERSION_MINOR
#undef GCROOTS_VERSION_PATCHLEVEL
#undef GCROOTS_API_REVISION
#undef GCROOTS_VERSION_REQUIRE

/* gcroots/gcroots.c */
#undef static
#undef l_findee
#undef l_found
