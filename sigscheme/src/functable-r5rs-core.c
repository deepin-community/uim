/*===========================================================================
 *  Filename : functable-r5rs-core.c
 *  About    : Built-in function table
 *             This file is auto-generated by build_func_table.rb
 *
 *  Copyright (C) 2005-2006 Kazuki Ohta <mover AT hct.zaq.ne.jp>
 *  Copyright (c) 2007-2008 SigScheme Project <uim-en AT googlegroups.com>
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of authors nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 *  IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
===========================================================================*/

#include <stddef.h>

#include "sigscheme.h"


static const struct scm_func_registration_info scm_functable_r5rs_core[] = {
    /* eval.c */
    { "eval", (ScmFuncType)scm_p_eval, SCM_PROCEDURE_FIXED_2 },
    { "apply", (ScmFuncType)scm_p_apply, SCM_PROCEDURE_VARIADIC_TAILREC_2 },
    { "scheme-report-environment", (ScmFuncType)scm_p_scheme_report_environment, SCM_PROCEDURE_FIXED_1 },
    { "null-environment", (ScmFuncType)scm_p_null_environment, SCM_PROCEDURE_FIXED_1 },
    { "interaction-environment", (ScmFuncType)scm_p_interaction_environment, SCM_PROCEDURE_FIXED_0 },

    /* procedure.c */
    { "eq?", (ScmFuncType)scm_p_eqp, SCM_PROCEDURE_FIXED_2 },
    { "eqv?", (ScmFuncType)scm_p_eqvp, SCM_PROCEDURE_FIXED_2 },
    { "equal?", (ScmFuncType)scm_p_equalp, SCM_PROCEDURE_FIXED_2 },
    { "not", (ScmFuncType)scm_p_not, SCM_PROCEDURE_FIXED_1 },
    { "boolean?", (ScmFuncType)scm_p_booleanp, SCM_PROCEDURE_FIXED_1 },
    { "symbol?", (ScmFuncType)scm_p_symbolp, SCM_PROCEDURE_FIXED_1 },
    { "symbol->string", (ScmFuncType)scm_p_symbol2string, SCM_PROCEDURE_FIXED_1 },
    { "string->symbol", (ScmFuncType)scm_p_string2symbol, SCM_PROCEDURE_FIXED_1 },
    { "procedure?", (ScmFuncType)scm_p_procedurep, SCM_PROCEDURE_FIXED_1 },
    { "map", (ScmFuncType)scm_p_map, SCM_PROCEDURE_VARIADIC_1 },
    { "for-each", (ScmFuncType)scm_p_for_each, SCM_PROCEDURE_VARIADIC_1 },
    { "call-with-current-continuation", (ScmFuncType)scm_p_call_with_current_continuation, SCM_PROCEDURE_FIXED_TAILREC_1 },
    { "values", (ScmFuncType)scm_p_values, SCM_PROCEDURE_VARIADIC_0 },
    { "call-with-values", (ScmFuncType)scm_p_call_with_values, SCM_PROCEDURE_FIXED_TAILREC_2 },
    { "dynamic-wind", (ScmFuncType)scm_p_dynamic_wind, SCM_PROCEDURE_FIXED_3 },

    /* list.c */
    { "pair?", (ScmFuncType)scm_p_pairp, SCM_PROCEDURE_FIXED_1 },
    { "cons", (ScmFuncType)scm_p_cons, SCM_PROCEDURE_FIXED_2 },
    { "car", (ScmFuncType)scm_p_car, SCM_PROCEDURE_FIXED_1 },
    { "cdr", (ScmFuncType)scm_p_cdr, SCM_PROCEDURE_FIXED_1 },
    { "set-car!", (ScmFuncType)scm_p_set_carx, SCM_PROCEDURE_FIXED_2 },
    { "set-cdr!", (ScmFuncType)scm_p_set_cdrx, SCM_PROCEDURE_FIXED_2 },
    { "caar", (ScmFuncType)scm_p_caar, SCM_PROCEDURE_FIXED_1 },
    { "cadr", (ScmFuncType)scm_p_cadr, SCM_PROCEDURE_FIXED_1 },
    { "cdar", (ScmFuncType)scm_p_cdar, SCM_PROCEDURE_FIXED_1 },
    { "cddr", (ScmFuncType)scm_p_cddr, SCM_PROCEDURE_FIXED_1 },
    { "caddr", (ScmFuncType)scm_p_caddr, SCM_PROCEDURE_FIXED_1 },
    { "cdddr", (ScmFuncType)scm_p_cdddr, SCM_PROCEDURE_FIXED_1 },
    { "null?", (ScmFuncType)scm_p_nullp, SCM_PROCEDURE_FIXED_1 },
    { "list?", (ScmFuncType)scm_p_listp, SCM_PROCEDURE_FIXED_1 },
    { "list", (ScmFuncType)scm_p_list, SCM_PROCEDURE_VARIADIC_0 },
    { "length", (ScmFuncType)scm_p_length, SCM_PROCEDURE_FIXED_1 },
    { "append", (ScmFuncType)scm_p_append, SCM_PROCEDURE_VARIADIC_0 },
    { "reverse", (ScmFuncType)scm_p_reverse, SCM_PROCEDURE_FIXED_1 },
    { "list-tail", (ScmFuncType)scm_p_list_tail, SCM_PROCEDURE_FIXED_2 },
    { "list-ref", (ScmFuncType)scm_p_list_ref, SCM_PROCEDURE_FIXED_2 },
    { "memq", (ScmFuncType)scm_p_memq, SCM_PROCEDURE_FIXED_2 },
    { "memv", (ScmFuncType)scm_p_memv, SCM_PROCEDURE_FIXED_2 },
    { "member", (ScmFuncType)scm_p_member, SCM_PROCEDURE_FIXED_2 },
    { "assq", (ScmFuncType)scm_p_assq, SCM_PROCEDURE_FIXED_2 },
    { "assv", (ScmFuncType)scm_p_assv, SCM_PROCEDURE_FIXED_2 },
    { "assoc", (ScmFuncType)scm_p_assoc, SCM_PROCEDURE_FIXED_2 },

    { NULL, NULL, SCM_FUNCTYPE_INVALID }
};
