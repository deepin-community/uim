/*===========================================================================
 *  Filename : storage-fatty.h
 *  About    : Storage abstraction (fatty representation)
 *
 *  Copyright (C) 2005      Kazuki Ohta <mover AT hct.zaq.ne.jp>
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
#ifndef __STORAGE_FATTY_H
#define __STORAGE_FATTY_H

/*
 * Internal representation defined in this file MUST NOT directly touched by
 * libsscm users. Use abstract public APIs defined in sigscheme.h.
 */

/*
 * storage-fatty.h: A storage implementation with fatty represenation
 *
 * This is the most simple storage implementation for SigScheme. The features
 * are below.
 *
 * - Supports all data models of ILP32, ILP32 with 64-bit long long, LLP64,
 *   LP64 and ILP64
 * - Consumes larger memory space (twice of storage-compact)
 * - Can hold full-width integer
 * - Easy to read and recognize
 * - Easy to debug upper layer of SigScheme and its clients
 * - Easy to extend and test experimental features
 */

#include <stddef.h>

/* Don't include scmport.h. The implementations are internal and should not be
 * exposed to libsscm users via installation of this file. */

#ifdef __cplusplus
/* extern "C" { */
#endif

/*=======================================
   Type Definitions
=======================================*/
/* Since this storage implementation does not have any immediate values,
 * (sizeof(ScmObj) == sizeof(ScmCell *)) is ensured even if sizeof(scm_int_t)
 * is larger than sizeof(ScmObj). */
typedef struct ScmCell_ ScmCell;
typedef ScmCell *ScmObj;
typedef ScmObj *ScmRef;

#define ALIGNOF_SCMOBJ ALIGNOF_VOID_P
#define SIZEOF_SCMOBJ  SIZEOF_VOID_P

typedef ScmObj (*ScmFuncType)();

struct ScmCell_ {
    union {
        struct {
            enum ScmObjType type;
            char gcmark, immutable, pad2, pad3;
        } v;

        /* to align against 64-bit primitives */
        struct {
            scm_uintobj_t slot0;
            scm_uintobj_t slot1;
        } strut;
    } attr;

    /*
     * Pointer members should be placed first for efficient alignment when
     * strict alignment is not forced by the compiler/processor.
     */
    union {
        struct {
            scm_int_t value;
        } integer;

        struct {
            ScmObj car;
            ScmObj cdr;
        } cons;

        struct {
            char *name;
            ScmObj value;
        } symbol;

        struct {
            scm_ichar_t value;
        } character;

        struct {
            char *str;
            scm_int_t len;  /* number of (multibyte) chars */
        } string;

        struct {
            ScmFuncType ptr;
            enum ScmFuncTypeCode type;
        } function;

        struct {
            ScmObj exp;
            ScmObj env;
        } closure;

        struct {
            ScmObj *vec;
            scm_int_t len;
        } vector;

        struct {
            struct ScmCharPort_ *impl;
            enum ScmPortFlag flag;
        } port;

        struct {
            void *opaque;
            scm_int_t tag;
        } continuation;

#if !SCM_USE_VALUECONS
        struct {
            ScmObj lst;
        } value_packet;
#endif

        struct {
            void *value;
        } c_pointer;

        struct {
            ScmCFunc value;
        } c_func_pointer;

#if SCM_USE_HYGIENIC_MACRO
        struct {
            ScmObj rules;
            ScmPackedEnv env;
        } hmacro;

        struct {
            ScmObj sym;
            ScmPackedEnv env;
        } farsym;

        struct {
            ScmObj obj;
            scm_int_t meta;
        } subpat;
#endif /* SCM_USE_HYGIENIC_MACRO */

        /* to align against 64-bit primitives */
        struct {
            scm_uintobj_t slot2;
            scm_uintobj_t slot3;
        } strut;
    } obj;
};

/*=======================================
  Object Representation Information
=======================================*/
#define SCM_SAL_HAS_CHAR     1
#define SCM_SAL_HAS_RATIONAL 0
#define SCM_SAL_HAS_REAL     0
#define SCM_SAL_HAS_COMPLEX  0
#define SCM_SAL_HAS_STRING   1
#define SCM_SAL_HAS_VECTOR   1

#define SCM_SAL_HAS_IMMUTABLE_CONS   1
#define SCM_SAL_HAS_IMMUTABLE_STRING 1
#define SCM_SAL_HAS_IMMUTABLE_VECTOR 1

/* for optimization */
#define SCM_SAL_HAS_IMMEDIATE_CHAR_ONLY     0
#define SCM_SAL_HAS_IMMEDIATE_NUMBER_ONLY   0
#define SCM_SAL_HAS_IMMEDIATE_INT_ONLY      0
#define SCM_SAL_HAS_IMMEDIATE_RATIONAL_ONLY 0
#define SCM_SAL_HAS_IMMEDIATE_REAL_ONLY     0
#define SCM_SAL_HAS_IMMEDIATE_COMPLEX_ONLY  0

#define SCM_SAL_PTR_BITS    (sizeof(void *) * CHAR_BIT)

#define SCM_SAL_CHAR_BITS   (sizeof(scm_ichar_t) * CHAR_BIT)
#define SCM_SAL_CHAR_MAX    SCM_ICHAR_T_MAX

#define SCM_SAL_INT_BITS    (sizeof(scm_int_t) * CHAR_BIT)
#define SCM_SAL_INT_MAX     SCM_INT_T_MAX
#define SCM_SAL_INT_MIN     SCM_INT_T_MIN

/* string length */
#define SCM_SAL_STRLEN_BITS SCM_INT_BITS
#define SCM_SAL_STRLEN_MAX  SCM_INT_MAX

/* vector length */
#define SCM_SAL_VECLEN_BITS SCM_INT_BITS
#define SCM_SAL_VECLEN_MAX  SCM_INT_MAX

/*=======================================
  Object Creators
=======================================*/
#if SCM_USE_VALUECONS
#define SCM_SAL_MAKE_VALUEPACKET(vals)                                       \
    (NULLP(vals) ? scm_null_values                                           \
                 : (SCM_ENTYPE(vals, ScmValuePacket), (vals)))
#endif /* SCM_USE_VALUECONS */

/*=======================================
   Accessors For Scheme Objects
=======================================*/
/* ScmObj Global Attribute */
#define SCM_SAL_TYPE(o)        ((o)->attr.v.type)
#define SCM_ENTYPE(o, objtype) ((o)->attr.v.type = (objtype))
#define SCM_MUTABLEP(o)        (!(o)->attr.v.immutable)
#define SCM_SET_MUTABLE(o)     ((o)->attr.v.immutable = scm_false)
#define SCM_SET_IMMUTABLE(o)   ((o)->attr.v.immutable = scm_true)

/* Real Accessors */
#define SCM_SAL_NUMBERP(o)             SCM_SAL_INTP(o)

#define SCM_SAL_INTP(o)                (SCM_TYPE(o) == ScmInt)
#define SCM_SAL_INT_VALUE(o)           (SCM_AS_INT(o)->obj.integer.value)
#define SCM_SAL_INT_SET_VALUE(o, val)  (SCM_INT_VALUE(o) = (val))
#define SCM_ISAL_INT_INIT(o, val)      (SCM_ENTYPE((o), ScmInt),        \
                                        SCM_INT_SET_VALUE((o), (val)))

#define SCM_SAL_CONSP(o)               (SCM_TYPE(o) == ScmCons)
/* don't use as lvalue */
#define SCM_SAL_CONS_CAR(o)            (SCM_AS_CONS(o)->obj.cons.car + 0)
#define SCM_SAL_CONS_CDR(o)            (SCM_AS_CONS(o)->obj.cons.cdr + 0)
#define SCM_SAL_CONS_SET_CAR(o, kar)   (SCM_AS_CONS(o)->obj.cons.car = (kar))
#define SCM_SAL_CONS_SET_CDR(o, kdr)   (SCM_AS_CONS(o)->obj.cons.cdr = (kdr))
#define SCM_SAL_CONS_MUTABLEP(o)       (SCM_MUTABLEP(o))
#define SCM_SAL_CONS_SET_MUTABLE(o)    (SCM_SET_MUTABLE(o))
#define SCM_SAL_CONS_SET_IMMUTABLE(o)  (SCM_SET_IMMUTABLE(o))
#define SCM_ISAL_CONS_INIT(o, kar, kdr)         \
    (SCM_ENTYPE((o), ScmCons),                  \
     SCM_CONS_SET_CAR((o), (kar)),              \
     SCM_CONS_SET_CDR((o), (kdr)),              \
     SCM_CONS_SET_MUTABLE(o))
#define SCM_ISAL_IMMUTABLE_CONS_INIT(o, kar, kdr)       \
    (SCM_ENTYPE((o), ScmCons),                          \
     SCM_CONS_SET_CAR((o), (kar)),                      \
     SCM_CONS_SET_CDR((o), (kdr)),                      \
     SCM_CONS_SET_IMMUTABLE(o))

#define SCM_SAL_SYMBOLP(o)             (SCM_TYPE(o) == ScmSymbol)
#define SCM_SAL_SYMBOL_NAME(o)         (SCM_AS_SYMBOL(o)->obj.symbol.name)
#define SCM_SAL_SYMBOL_SET_NAME(o, name) (SCM_SYMBOL_NAME(o) = (name))
#define SCM_SAL_SYMBOL_VCELL(o)        (SCM_AS_SYMBOL(o)->obj.symbol.value)
#define SCM_SAL_SYMBOL_SET_VCELL(o, val) (SCM_SYMBOL_VCELL(o) = (val))
#define SCM_ISAL_SYMBOL_INIT(o, n, v)  (SCM_ENTYPE((o), ScmSymbol),     \
                                        SCM_SYMBOL_SET_NAME((o), (n)),  \
                                        SCM_SYMBOL_SET_VCELL((o), (v)))

#define SCM_SAL_CHARP(o)               (SCM_TYPE(o) == ScmChar)
#define SCM_SAL_CHAR_VALUE(o)          (SCM_AS_CHAR(o)->obj.character.value)
#define SCM_SAL_CHAR_SET_VALUE(o, val) (SCM_CHAR_VALUE(o) = (val))
#define SCM_ISAL_CHAR_INIT(o, val)     (SCM_ENTYPE((o), ScmChar),       \
                                        SCM_CHAR_SET_VALUE((o), (val)))

#define SCM_SAL_STRINGP(o)              (SCM_TYPE(o) == ScmString)
#define SCM_SAL_STRING_STR(o)           (SCM_AS_STRING(o)->obj.string.str)
#define SCM_SAL_STRING_SET_STR(o, val)  (SCM_STRING_STR(o) = (val))
#define SCM_SAL_STRING_LEN(o)           (SCM_AS_STRING(o)->obj.string.len)
#define SCM_SAL_STRING_SET_LEN(o, len)  (SCM_STRING_LEN(o) = (len))
#define SCM_SAL_STRING_MUTABLEP(o)      (SCM_MUTABLEP(o))
#define SCM_SAL_STRING_SET_MUTABLE(o)   (SCM_SET_MUTABLE(o))
#define SCM_SAL_STRING_SET_IMMUTABLE(o) (SCM_SET_IMMUTABLE(o))
#define SCM_ISAL_STRING_INIT(o, s, l, mutp)     \
    (SCM_ENTYPE((o), ScmString),                \
     SCM_STRING_SET_STR((o), (s)),              \
     SCM_STRING_SET_LEN((o), (l)),              \
     mutp ? SCM_STRING_SET_MUTABLE(o)           \
          : SCM_STRING_SET_IMMUTABLE(o))
#define SCM_ISAL_MUTABLE_STRING_INIT(o, s, l)           \
    SCM_ISAL_STRING_INIT((o), (s), (l), scm_true)
#define SCM_ISAL_IMMUTABLE_STRING_INIT(o, s, l)         \
    SCM_ISAL_STRING_INIT((o), (s), (l), scm_false)

#define SCM_SAL_FUNCP(o)                   (SCM_TYPE(o) == ScmFunc)
#define SCM_SAL_FUNC_TYPECODE(o)           (SCM_AS_FUNC(o)->obj.function.type)
#define SCM_SAL_FUNC_SET_TYPECODE(o, type) (SCM_FUNC_TYPECODE(o) = (type))
#define SCM_SAL_FUNC_CFUNC(o)              (SCM_AS_FUNC(o)->obj.function.ptr)
#define SCM_SAL_FUNC_SET_CFUNC(o, func)                                      \
    (SCM_FUNC_CFUNC(o) = (ScmFuncType)(func))
#define SCM_ISAL_FUNC_INIT(o, t, f) (SCM_ENTYPE((o), ScmFunc),           \
                                     SCM_FUNC_SET_TYPECODE((o), (t)),    \
                                     SCM_FUNC_SET_CFUNC((o), (f)))       \

#define SCM_SAL_CLOSUREP(o)               (SCM_TYPE(o) == ScmClosure)
#define SCM_SAL_CLOSURE_EXP(o)            (SCM_AS_CLOSURE(o)->obj.closure.exp)
#define SCM_SAL_CLOSURE_SET_EXP(o, exp)   (SCM_CLOSURE_EXP(o) = (exp))
#define SCM_SAL_CLOSURE_ENV(o)            (SCM_AS_CLOSURE(o)->obj.closure.env)
#define SCM_SAL_CLOSURE_SET_ENV(o, env)   (SCM_CLOSURE_ENV(o) = (env))
#define SCM_ISAL_CLOSURE_INIT(o, x, e)    (SCM_ENTYPE((o), ScmClosure),       \
                                           SCM_CLOSURE_SET_EXP((o), (x)), \
                                           SCM_CLOSURE_SET_ENV((o), (e)))

#define SCM_SAL_VECTORP(o)                (SCM_TYPE(o) == ScmVector)
#define SCM_SAL_VECTOR_VEC(o)             (SCM_AS_VECTOR(o)->obj.vector.vec)
#define SCM_SAL_VECTOR_SET_VEC(o, vec)    (SCM_VECTOR_VEC(o) = (vec))
#define SCM_SAL_VECTOR_LEN(o)             (SCM_AS_VECTOR(o)->obj.vector.len)
#define SCM_SAL_VECTOR_SET_LEN(o, len)    (SCM_VECTOR_LEN(o) = (len))
#define SCM_SAL_VECTOR_MUTABLEP(o)        (SCM_MUTABLEP(o))
#define SCM_SAL_VECTOR_SET_MUTABLE(o)     (SCM_SET_MUTABLE(o))
#define SCM_SAL_VECTOR_SET_IMMUTABLE(o)   (SCM_SET_IMMUTABLE(o))
#define SCM_ISAL_VECTOR_INIT(o, v, l, mutp)     \
    (SCM_ENTYPE((o), ScmVector),                \
     SCM_VECTOR_SET_VEC((o), (v)),              \
     SCM_VECTOR_SET_LEN((o), (l)),              \
     mutp ? SCM_VECTOR_SET_MUTABLE(o)           \
          : SCM_VECTOR_SET_IMMUTABLE(o))
#define SCM_ISAL_MUTABLE_VECTOR_INIT(o, v, l)           \
    SCM_ISAL_VECTOR_INIT((o), (v), (l), scm_true)
#define SCM_ISAL_IMMUTABLE_VECTOR_INIT(o, v, l)         \
    SCM_ISAL_VECTOR_INIT((o), (v), (l), scm_false)

#define SCM_SAL_PORTP(o)               (SCM_TYPE(o) == ScmPort)
#define SCM_SAL_PORT_FLAG(o)           (SCM_AS_PORT(o)->obj.port.flag)
#define SCM_SAL_PORT_SET_FLAG(o, flag) (SCM_PORT_FLAG(o) = (flag))
#define SCM_SAL_PORT_IMPL(o)           (SCM_AS_PORT(o)->obj.port.impl)
#define SCM_SAL_PORT_SET_IMPL(o, impl) (SCM_PORT_IMPL(o) = (impl))
#define SCM_ISAL_PORT_INIT(o, i, f)    (SCM_ENTYPE((o), ScmPort),        \
                                        SCM_PORT_SET_IMPL((o), (i)),     \
                                        SCM_PORT_SET_FLAG((o), (f)))

#define SCM_SAL_CONTINUATIONP(o)       (SCM_TYPE(o) == ScmContinuation)
#define SCM_SAL_CONTINUATION_OPAQUE(o)                                       \
    (SCM_AS_CONTINUATION(o)->obj.continuation.opaque)
#define SCM_SAL_CONTINUATION_SET_OPAQUE(o, val)                              \
    (SCM_CONTINUATION_OPAQUE(o) = (val))
#define SCM_SAL_CONTINUATION_TAG(o)                                          \
    (SCM_AS_CONTINUATION(o)->obj.continuation.tag)
#define SCM_SAL_CONTINUATION_SET_TAG(o, val)                                 \
    (SCM_CONTINUATION_TAG(o) = (val))
#define SCM_ISAL_CONTINUATION_INIT(o, v, t)     \
    (SCM_ENTYPE((o), ScmContinuation),          \
     SCM_SAL_CONTINUATION_SET_OPAQUE((o), (v)), \
     SCM_SAL_CONTINUATION_SET_TAG((o), (t)))

#if SCM_USE_VALUECONS
/* to modify a VALUECONS, rewrite its type to cons by SCM_ENTYPE(vcons,
 * ScmCons) */
#define SCM_SAL_VALUEPACKETP(o)        (SCM_TYPE(o) == ScmValuePacket)
#define SCM_SAL_NULLVALUESP(o)         (EQ((o), scm_null_values))
#define SCM_SAL_VALUEPACKET_VALUES(o)                                        \
    ((SCM_NULLVALUESP(o)) ? SCM_NULL : (SCM_ENTYPE((o), ScmCons), (o)))
#define SCM_SAL_VALUECONS_CAR(o)       (SCM_AS_VALUEPACKET(o)->obj.cons.car)
#define SCM_SAL_VALUECONS_CDR(o)       (SCM_AS_VALUEPACKET(o)->obj.cons.cdr)
#else /* SCM_USE_VALUECONS */
#define SCM_SAL_VALUEPACKETP(o)        (SCM_TYPE(o) == ScmValuePacket)
#define SCM_SAL_VALUEPACKET_VALUES(o)                                        \
    (SCM_AS_VALUEPACKET(o)->obj.value_packet.lst)
#define SCM_SAL_VALUEPACKET_SET_VALUES(o, v) (SCM_VALUEPACKET_VALUES(o) = (v))
#define SCM_ISAL_VALUEPACKET_INIT(o, v) (SCM_ENTYPE((o), ScmValuePacket),     \
                                         SCM_VALUEPACKET_SET_VALUES((o), (v)))
#endif /* SCM_USE_VALUECONS */

#if (SCM_USE_HYGIENIC_MACRO || SCM_USE_UNHYGIENIC_MACRO)
#define SCM_SAL_MACROP(o)              (SCM_TYPE(o) == ScmMacro)
#if (SCM_USE_HYGIENIC_MACRO && SCM_USE_UNHYGIENIC_MACRO)
#define SCM_SAL_HMACROP(o)             (SCM_SAL_MACROP(o) && /* TODO */)
#else  /* not SCM_USE_UNHYGIENIC_MACRO */
#define SCM_SAL_HMACROP(o)             (SCM_SAL_MACROP(o))
#endif /* not SCM_USE_UNHYGIENIC_MACRO */
#define SCM_SAL_HMACRO_RULES(o)        (SCM_AS_HMACRO(o)->obj.hmacro.rules)
#define SCM_SAL_HMACRO_SET_RULES(o, r) (SCM_SAL_HMACRO_RULES(o) = (r))
#define SCM_SAL_HMACRO_ENV(o)          (SCM_AS_HMACRO(o)->obj.hmacro.env)
#define SCM_SAL_HMACRO_SET_ENV(o, e)   (SCM_SAL_HMACRO_ENV(o) = (e))
#define SCM_ISAL_HMACRO_INIT(o, r, e)  (SCM_ENTYPE((o), ScmMacro),      \
                                        SCM_HMACRO_SET_RULES((o), (r)), \
                                        SCM_HMACRO_SET_ENV((o), (e)))

#define SCM_SAL_FARSYMBOLP(o)           (SCM_TYPE(o) == ScmFarsymbol)
#define SCM_SAL_FARSYMBOL_SYM(o)        (SCM_AS_FARSYMBOL(o)->obj.farsym.sym)
#define SCM_SAL_FARSYMBOL_SET_SYM(o, s) (SCM_SAL_FARSYMBOL_SYM(o) = (s))
#define SCM_SAL_FARSYMBOL_ENV(o)        (SCM_AS_FARSYMBOL(o)->obj.farsym.env)
#define SCM_SAL_FARSYMBOL_SET_ENV(o, e) (SCM_SAL_FARSYMBOL_ENV(o) = (e))
#define SCM_ISAL_FARSYMBOL_INIT(o, s, e) (SCM_ENTYPE((o), ScmFarsymbol),   \
                                          SCM_FARSYMBOL_SET_SYM((o), (s)), \
                                          SCM_FARSYMBOL_SET_ENV((o), (e)))

#define SCM_SAL_SUBPATP(o)              (SCM_TYPE(o) == ScmSubpat)
#define SCM_SAL_SUBPAT_OBJ(o)           (SCM_AS_SUBPAT(o)->obj.subpat.obj)
#define SCM_SAL_SUBPAT_META(o)          (SCM_AS_SUBPAT(o)->obj.subpat.meta)
#define SCM_SAL_SUBPAT_SET_OBJ(o, x)    (SCM_SAL_SUBPAT_OBJ(o) = (x))
#define SCM_SAL_SUBPAT_SET_META(o, m)   (SCM_SAL_SUBPAT_META(o) = (m))
#define SCM_ISAL_SUBPAT_INIT(o, x, m)   (SCM_ENTYPE((o), ScmSubpat),    \
                                         SCM_SUBPAT_SET_OBJ((o), (x)),  \
                                         SCM_SUBPAT_SET_META((o), (m)))
#endif /* SCM_USE_HYGIENIC_MACRO */

/*===========================================================================
  Special Constants (such as SCM_NULL)
===========================================================================*/
#define SCM_SAL_CONSTANTP(o)           (SCM_TYPE(o) == ScmConstant)

/*===========================================================================
  C Pointer Object
===========================================================================*/
#define SCM_SAL_C_POINTERP(o)           (SCM_TYPE(o) == ScmCPointer)
#define SCM_SAL_C_POINTER_VALUE(o)                                           \
    (SCM_AS_C_POINTER(o)->obj.c_pointer.value)
#define SCM_SAL_C_POINTER_SET_VALUE(o, ptr)                                  \
    (SCM_C_POINTER_VALUE(o) = (ptr))
#define SCM_ISAL_C_POINTER_INIT(o, ptr)         \
    (SCM_ENTYPE((o), ScmCPointer),              \
     SCM_C_POINTER_SET_VALUE((o), (ptr)))
#define SCM_SAL_C_FUNCPOINTERP(o)       (SCM_TYPE(o) == ScmCFuncPointer)
#define SCM_SAL_C_FUNCPOINTER_VALUE(o)                                       \
    (SCM_AS_C_FUNCPOINTER(o)->obj.c_func_pointer.value)
#define SCM_SAL_C_FUNCPOINTER_SET_VALUE(o, ptr)                              \
    (SCM_C_FUNCPOINTER_VALUE(o) = (ptr))
#define SCM_ISAL_C_FUNCPOINTER_INIT(o, ptr)     \
    (SCM_ENTYPE((o), ScmCFuncPointer),          \
     SCM_C_FUNCPOINTER_SET_VALUE((o), (ptr)))

/*===========================================================================
  GC Related Operations
===========================================================================*/
#define SCM_SAL_FREECELLP(o)           (SCM_TYPE(o) == ScmFreeCell)
#define SCM_SAL_AS_FREECELL(o)         (SCM_ASSERT_TYPE(SCM_FREECELLP(o), (o)))
#define SCM_SAL_FREECELL_NEXT(o)       (SCM_AS_FREECELL(o)->obj.cons.car)
#define SCM_SAL_FREECELL_FREESLOT(o)   (SCM_AS_FREECELL(o)->obj.cons.cdr)
#define SCM_SAL_FREECELL_SET_NEXT(o, next)  (SCM_FREECELL_NEXT(o) = (next))
#define SCM_SAL_FREECELL_SET_FREESLOT(o, v) (SCM_FREECELL_FREESLOT(o) = (v))
#define SCM_SAL_FREECELL_CLEAR_FREESLOT(o)                                   \
    SCM_SAL_FREECELL_SET_FREESLOT((o), SCM_FALSE)

#define SCM_ISAL_CELL_FREECELLP(c)     (SCM_FREECELLP(c))
/* To avoid void-returning macro SCM_CELL_UNMARK(), SCM_ISAL_CELL_UNMARK() is
 * directly used here. */
#define SCM_ISAL_CELL_RECLAIM_CELL(c, next)                             \
    (SCM_ENTYPE((c), ScmFreeCell),                                      \
     SCM_ISAL_CELL_UNMARK(c),                                           \
     SCM_FREECELL_SET_NEXT((c), (next)),                                \
     SCM_FREECELL_CLEAR_FREESLOT(c),                                    \
     (ScmObj)(c))

#define SCM_ISAL_MARKEDP(o)      ((o)->attr.v.gcmark)
#define SCM_ISAL_MARK(o)         ((o)->attr.v.gcmark = scm_true)
#define SCM_ISAL_CELL_MARKEDP(c) ((c)->attr.v.gcmark)
#define SCM_ISAL_CELL_UNMARK(c)  ((c)->attr.v.gcmark = scm_false)

/*===========================================================================
  Abstract ScmObj Reference For Storage-Representation Independent Efficient
  List Operations
===========================================================================*/
#define SCM_SAL_INVALID_REF   (NULL)

#define SCM_SAL_REF_CAR(kons)     (&SCM_AS_CONS(kons)->obj.cons.car)
#define SCM_SAL_REF_CDR(kons)     (&SCM_AS_CONS(kons)->obj.cons.cdr)
#define SCM_SAL_REF_OFF_HEAP(obj) (&(obj))

/* SCM_DEREF(ref) is not permitted to be used as lvalue */
#define SCM_SAL_DEREF(ref)    (*(ref) + 0)

/* RFC: Is there a better name? */
#define SCM_SAL_SET(ref, obj) (*(ref) = (obj))

/*===========================================================================
  Special Constants and Predicates
===========================================================================*/
#define SCM_SAL_INVALID  (NULL)
#define SCM_SAL_NULL     scm_const_null
#define SCM_SAL_TRUE     scm_const_true
#if SCM_COMPAT_SIOD_BUGS
#define SCM_SAL_FALSE    scm_const_null
#else
#define SCM_SAL_FALSE    scm_const_false
#endif /* SCM_COMPAT_SIOD_BUGS */
#define SCM_SAL_EOF      scm_const_eof
#define SCM_SAL_UNBOUND  scm_const_unbound
#define SCM_SAL_UNDEF    scm_const_undef

#define SCM_SAL_EQ(a, b) ((a) == (b))

/* storage.c */
SCM_GLOBAL_VARS_BEGIN(storage_fatty);
ScmObj scm_const_null, scm_const_true, scm_const_false, scm_const_eof;
ScmObj scm_const_unbound, scm_const_undef;
SCM_GLOBAL_VARS_END(storage_fatty);
#define scm_const_null    SCM_GLOBAL_VAR(storage_fatty, scm_const_null)
#define scm_const_true    SCM_GLOBAL_VAR(storage_fatty, scm_const_true)
#define scm_const_false   SCM_GLOBAL_VAR(storage_fatty, scm_const_false)
#define scm_const_eof     SCM_GLOBAL_VAR(storage_fatty, scm_const_eof)
#define scm_const_unbound SCM_GLOBAL_VAR(storage_fatty, scm_const_unbound)
#define scm_const_undef   SCM_GLOBAL_VAR(storage_fatty, scm_const_undef)
SCM_DECLARE_EXPORTED_VARS(storage_fatty);

#ifdef __cplusplus
/* } */
#endif

#include "storage-common.h"

#endif /* __STORAGE_FATTY_H */
