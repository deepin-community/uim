/*===========================================================================
 *  Filename : procedure.c
 *  About    : Miscellaneous R5RS procedures
 *
 *  Copyright (C) 2005      Kazuki Ohta <mover AT hct.zaq.ne.jp>
 *  Copyright (C) 2005-2006 Jun Inoue <jun.lambda AT gmail.com>
 *  Copyright (C) 2005-2006 YAMAMOTO Kengo <yamaken AT bp.iij4u.or.jp>
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

#include <config.h>

#include "sigscheme.h"
#include "sigschemeinternal.h"

/*=======================================
  File Local Macro Definitions
=======================================*/
#define ERRMSG_UNEVEN_MAP_ARGS "unequal-length lists are passed as arguments"

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  Variable Definitions
=======================================*/
/* canonical internal encoding for identifiers */
SCM_DEFINE_EXPORTED_VARS(procedure);

/*=======================================
  File Local Function Declarations
=======================================*/

/*=======================================
  Function Definitions
=======================================*/
/*===========================================================================
  R5RS : 6.1 Equivalence predicates
===========================================================================*/
SCM_EXPORT ScmObj
scm_p_eqp(ScmObj obj1, ScmObj obj2)
{
    DECLARE_FUNCTION("eq?", procedure_fixed_2);

    return MAKE_BOOL(EQ(obj1, obj2));
}

SCM_EXPORT ScmObj
scm_p_eqvp(ScmObj obj1, ScmObj obj2)
{
#if SCM_HAS_EQVP

#define scm_p_eqvp error_eqvp_recursed__ /* Safety measure. */
    return EQVP(obj1, obj2);
#undef scm_p_eqvp

#else  /* don't have inlined EQVP() */

#if (!(SCM_HAS_IMMEDIATE_NUMBER_ONLY && SCM_HAS_IMMEDIATE_CHAR_ONLY))
    enum ScmObjType type;
#endif
    DECLARE_FUNCTION("eqv?", procedure_fixed_2);

    if (EQ(obj1, obj2))
        return SCM_TRUE;

#if (!(SCM_HAS_IMMEDIATE_NUMBER_ONLY && SCM_HAS_IMMEDIATE_CHAR_ONLY))
    type = SCM_TYPE(obj1);

    /* different type */
    if (type != SCM_TYPE(obj2))
        return SCM_FALSE;

    /* same type */
    switch (type) {
#if (SCM_USE_INT && !SCM_HAS_IMMEDIATE_INT_ONLY)
    case ScmInt:
        return MAKE_BOOL(SCM_INT_VALUE(obj1) == SCM_INT_VALUE(obj2));
#endif

#if (SCM_USE_CHAR && !SCM_HAS_IMMEDIATE_CHAR_ONLY)
    case ScmChar:
        return MAKE_BOOL(SCM_CHAR_VALUE(obj1) == SCM_CHAR_VALUE(obj2));
#endif

    default:
        break;
    }
#endif /* (!(SCM_HAS_IMMEDIATE_NUMBER_ONLY && SCM_HAS_IMMEDIATE_CHAR_ONLY)) */

    return SCM_FALSE;

#endif /* don't have inlined EQVP() */
}

SCM_EXPORT ScmObj
scm_p_equalp(ScmObj obj1, ScmObj obj2)
{
    enum ScmObjType type;
    ScmObj elm1, elm2;
#if SCM_USE_VECTOR
    ScmObj *v1, *v2;
    scm_int_t i, len;
#endif
    DECLARE_FUNCTION("equal?", procedure_fixed_2);

    if (EQ(obj1, obj2))
        return SCM_TRUE;

    type = SCM_TYPE(obj1);

    /* different type */
    if (type != SCM_TYPE(obj2))
        return SCM_FALSE;

    /* same type */
    switch (type) {
#if (SCM_USE_INT && !SCM_HAS_IMMEDIATE_INT_ONLY)
    case ScmInt:
        return MAKE_BOOL(SCM_INT_VALUE(obj1) == SCM_INT_VALUE(obj2));
#endif

#if (SCM_USE_CHAR && !SCM_HAS_IMMEDIATE_CHAR_ONLY)
    case ScmChar:
        return MAKE_BOOL(SCM_CHAR_VALUE(obj1) == SCM_CHAR_VALUE(obj2));
#endif

#if SCM_USE_STRING
    case ScmString:
        return MAKE_BOOL(STRING_EQUALP(obj1, obj2));
#endif

    case ScmCons:
        for (; CONSP(obj1) && CONSP(obj2); obj1 = CDR(obj1), obj2 = CDR(obj2))
        {
            elm1 = CAR(obj1);
            elm2 = CAR(obj2);
            if (!EQ(elm1, elm2)
                && (SCM_TYPE(elm1) != SCM_TYPE(elm2)
                    || !EQUALP(elm1, elm2)))
                return SCM_FALSE;
        }
        /* compare last cdr */
        return (EQ(obj1, obj2)) ? SCM_TRUE : scm_p_equalp(obj1, obj2);

#if SCM_USE_VECTOR
    case ScmVector:
        len = SCM_VECTOR_LEN(obj1);
        if (len != SCM_VECTOR_LEN(obj2))
            return SCM_FALSE;

        v1 = SCM_VECTOR_VEC(obj1);
        v2 = SCM_VECTOR_VEC(obj2);
        for (i = 0; i < len; i++) {
            elm1 = v1[i];
            elm2 = v2[i];
            if (!EQ(elm1, elm2)
                && (SCM_TYPE(elm1) != SCM_TYPE(elm2)
                    || !EQUALP(elm1, elm2)))
                return SCM_FALSE;
        }
        return SCM_TRUE;
#endif

#if SCM_USE_SSCM_EXTENSIONS
    case ScmCPointer:
        return MAKE_BOOL(SCM_C_POINTER_VALUE(obj1)
                         == SCM_C_POINTER_VALUE(obj2));

    case ScmCFuncPointer:
        return MAKE_BOOL(SCM_C_FUNCPOINTER_VALUE(obj1)
                         == SCM_C_FUNCPOINTER_VALUE(obj2));
#endif

    default:
        break;
    }

    return SCM_FALSE;
}

/*===================================
  R5RS : 6.3 Other data types
===================================*/
/*===========================================================================
  R5RS : 6.3 Other data types : 6.3.1 Booleans
===========================================================================*/
SCM_EXPORT ScmObj
scm_p_not(ScmObj obj)
{
    DECLARE_FUNCTION("not", procedure_fixed_1);

    return MAKE_BOOL(FALSEP(obj));
}

SCM_EXPORT ScmObj
scm_p_booleanp(ScmObj obj)
{
    DECLARE_FUNCTION("boolean?", procedure_fixed_1);

    return MAKE_BOOL(EQ(obj, SCM_FALSE) || EQ(obj, SCM_TRUE));
}

/*===========================================================================
  R5RS : 6.3 Other data types : 6.3.3 Symbols
===========================================================================*/
SCM_EXPORT ScmObj
scm_p_symbolp(ScmObj obj)
{
    DECLARE_FUNCTION("symbol?", procedure_fixed_1);

    return MAKE_BOOL(SYMBOLP(obj));
}

SCM_EXPORT ScmObj
scm_p_symbol2string(ScmObj sym)
{
    DECLARE_FUNCTION("symbol->string", procedure_fixed_1);

    ENSURE_SYMBOL(sym);

    return CONST_STRING(SCM_SYMBOL_NAME(sym));
}

SCM_EXPORT ScmObj
scm_p_string2symbol(ScmObj str)
{
    DECLARE_FUNCTION("string->symbol", procedure_fixed_1);

    ENSURE_STRING(str);

    return scm_intern(SCM_STRING_STR(str));
}

/*=======================================
  R5RS : 6.4 Control Features
=======================================*/
SCM_EXPORT ScmObj
scm_p_procedurep(ScmObj obj)
{
    DECLARE_FUNCTION("procedure?", procedure_fixed_1);

    return MAKE_BOOL(PROCEDUREP(obj));
}

SCM_EXPORT ScmObj
scm_p_map(ScmObj proc, ScmObj args)
{
    DECLARE_FUNCTION("map", procedure_variadic_1);

    if (NULLP(args))
        ERR("wrong number of arguments");

    /* fast path for single arg case */
    if (NULLP(CDR(args)))
        return scm_map_single_arg(proc, CAR(args));

    /* multiple args case */
    return scm_map_multiple_args(proc, args, scm_false);
}

SCM_EXPORT ScmObj
scm_map_single_arg(ScmObj proc, ScmObj lst)
{
    ScmQueue q;
    ScmObj elm, ret;
    DECLARE_INTERNAL_FUNCTION("map");

    ret = SCM_NULL;
    SCM_QUEUE_POINT_TO(q, ret);
    FOR_EACH (elm, lst) {
        elm = scm_call(proc, LIST_1(elm));
        SCM_QUEUE_ADD(q, elm);
    }
    NO_MORE_ARG(lst);

    return ret;
}

SCM_EXPORT ScmObj
scm_map_multiple_args(ScmObj proc, ScmObj lsts, scm_bool allow_uneven_lists)
{
    ScmQueue retq, argq;
    ScmObj ret, elm, map_args, rest_lsts, lst;
    DECLARE_INTERNAL_FUNCTION("map");

    ret = SCM_NULL;
    SCM_QUEUE_POINT_TO(retq, ret);
    for (;;) {
        /* slice args */
        map_args = SCM_NULL;
        SCM_QUEUE_POINT_TO(argq, map_args);
        for (rest_lsts = lsts; CONSP(rest_lsts); rest_lsts = CDR(rest_lsts)) {
            lst = CAR(rest_lsts);
            if (CONSP(lst))
                SCM_QUEUE_ADD(argq, CAR(lst));
            else if (NULLP(lst))
                goto finish;
            else
                ERR_OBJ("invalid argument", lst);
            /* pop destructively */
            SET_CAR(rest_lsts, CDR(lst));
        }

        elm = scm_call(proc, map_args);
        SCM_QUEUE_ADD(retq, elm);
    }

 finish:
#if SCM_STRICT_ARGCHECK
    if (!allow_uneven_lists) {
        /* R5RS: 6.4 Control features
         * > If more than one list is given, then they must all be the same
         * length.  SigScheme rejects such user-error explicitly. */
        if (!EQ(lsts, rest_lsts))
            ERR(ERRMSG_UNEVEN_MAP_ARGS);
        FOR_EACH (lst, lsts) {
            if (!NULLP(lst))
                ERR(ERRMSG_UNEVEN_MAP_ARGS);
        }
        NO_MORE_ARG(lsts);
    }
#endif

    return ret;
}

SCM_EXPORT ScmObj
scm_p_for_each(ScmObj proc, ScmObj args)
{
    DECLARE_FUNCTION("for-each", procedure_variadic_1);

    scm_p_map(proc, args);

    return SCM_UNDEF;
}

#if SCM_USE_CONTINUATION
SCM_EXPORT ScmObj
scm_p_call_with_current_continuation(ScmObj proc, ScmEvalState *eval_state)
{
    DECLARE_FUNCTION("call-with-current-continuation",
                     procedure_fixed_tailrec_1);

    return scm_call_with_current_continuation(proc, eval_state);
}
#endif /* SCM_USE_CONTINUATION */

SCM_EXPORT ScmObj
scm_p_values(ScmObj args)
{
    DECLARE_FUNCTION("values", procedure_variadic_0);

    /* Values with one arg must return something that fits an ordinary
     * continuation. */
    if (LIST_1_P(args))
        return CAR(args);

    /* Otherwise, we'll return the values in a packet. */
    return SCM_MAKE_VALUEPACKET(args);
}

SCM_EXPORT ScmObj
scm_p_call_with_values(ScmObj producer, ScmObj consumer,
                       ScmEvalState *eval_state)
{
    ScmObj vals;
    DECLARE_FUNCTION("call-with-values", procedure_fixed_tailrec_2);

    vals = scm_call(producer, SCM_NULL);

    return LIST_3(scm_values_applier, consumer, vals);
}

#if SCM_USE_CONTINUATION
SCM_EXPORT ScmObj
scm_p_dynamic_wind(ScmObj before, ScmObj thunk, ScmObj after)
{
    DECLARE_FUNCTION("dynamic-wind", procedure_fixed_3);

    /* To reject non-procedure arguments before evaluating any other
     * arguments, ensure the types here instead of call(). */
    ENSURE_PROCEDURE(before);
    ENSURE_PROCEDURE(thunk);
    ENSURE_PROCEDURE(after);

    return scm_dynamic_wind(before, thunk, after);
}
#endif /* SCM_USE_CONTINUATION */
