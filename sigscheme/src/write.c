/*===========================================================================
 *  Filename : write.c
 *  About    : Object writer
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

/* TODO: make format.c independent */

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "sigscheme.h"
#include "sigschemeinternal.h"

/*=======================================
  File Local Macro Definitions
=======================================*/
#if SCM_USE_SRFI38
#if !SCM_USE_STRING
#define STRINGP(o)        0
#define SCM_STRING_LEN(o) 0
#endif
#if !SCM_USE_VECTOR
#undef  VECTORP
#define VECTORP(o) 0
#endif
#define INTERESTINGP(obj)                                                    \
    (CONSP(obj)                                                              \
     || (STRINGP(obj) && SCM_STRING_LEN(obj))                                \
     || CLOSUREP(obj)                                                        \
     || VECTORP(obj)                                                         \
     || VALUEPACKETP(obj)                                                    \
     || ERROBJP(obj))
#define OCCUPIED(ent)      (!EQ((ent)->key, SCM_INVALID))
#define HASH_EMPTY(table)  (!(table).used)
/* datum index */
#define DEFINING_DATUM     (-1)
#define NONDEFINING_DATUM  0
/* flags */
#define HASH_INSERT    1 /* insert key if it's not registered yet */
#define HASH_FIND      0
#endif /* SCM_USE_SRFI38 */

/*=======================================
  File Local Type Definitions
=======================================*/
enum ScmOutputType {
    UNKNOWN,
    AS_WRITE,  /* string is enclosed by ", char is written using #\ notation */
    AS_DISPLAY /* string and char is written as-is */
};

#if SCM_USE_SRFI38
typedef size_t hashval_t;

typedef struct {
    ScmObj key;
    scm_intobj_t datum;
} scm_hash_entry;

typedef struct {
    size_t size;  /* capacity; MUST be a power of 2 */
    size_t used;  /* population */
    scm_hash_entry *ents;
} scm_hash_table;

typedef struct {
    scm_hash_table seen; /* a table of seen objects */
    scm_intobj_t next_index;  /* the next index to use for #N# */
} scm_write_ss_context;
#endif /* SCM_USE_SRFI38 */

/*=======================================
  Variable Definitions
=======================================*/
#include "functable-r5rs-write.c"

SCM_DEFINE_EXPORTED_VARS(write);

#if SCM_USE_SRFI38
SCM_GLOBAL_VARS_BEGIN(static_write);
#define static
/* misc info in priting shared structures */
static scm_write_ss_context *l_write_ss_ctx;
#undef static
SCM_GLOBAL_VARS_END(static_write);
#define l_write_ss_ctx SCM_GLOBAL_VAR(static_write, l_write_ss_ctx)
SCM_DEFINE_STATIC_VARS(static_write);
#endif /* SCM_USE_SRFI38 */

/*=======================================
  File Local Function Declarations
=======================================*/
static void write_internal (ScmObj port, ScmObj obj, enum ScmOutputType otype);
static void write_obj      (ScmObj port, ScmObj obj, enum ScmOutputType otype);
#if SCM_USE_CHAR
static void write_char     (ScmObj port, ScmObj obj, enum ScmOutputType otype);
#endif
#if SCM_USE_STRING
static void write_string   (ScmObj port, ScmObj obj, enum ScmOutputType otype);
#endif
static void write_list     (ScmObj port, ScmObj lst, enum ScmOutputType otype);
#if SCM_USE_VECTOR
static void write_vector   (ScmObj port, ScmObj vec, enum ScmOutputType otype);
#endif
static void write_port     (ScmObj port, ScmObj obj, enum ScmOutputType otype);
static void write_constant (ScmObj port, ScmObj obj, enum ScmOutputType otype);
static void write_errobj   (ScmObj port, ScmObj obj, enum ScmOutputType otype);

#if SCM_USE_HYGIENIC_MACRO
static void write_farsymbol(ScmObj port, ScmObj obj, enum ScmOutputType otype);
#endif

#if SCM_USE_SRFI38
static void hash_grow(scm_hash_table *tab);
static scm_hash_entry *hash_lookup(scm_hash_table *tab,
                                   ScmObj key, scm_intobj_t datum, int flag);
static void write_ss_scan(ScmObj obj, scm_write_ss_context *ctx);
static scm_intobj_t get_shared_index(ScmObj obj);
static void write_ss_internal(ScmObj port, ScmObj obj, enum ScmOutputType otype);
#endif /* SCM_USE_SRFI38 */

/*=======================================
   Function Definitions
=======================================*/
SCM_EXPORT void
scm_init_writer(void)
{
    SCM_GLOBAL_VARS_INIT(write);
#if SCM_USE_SRFI38
    SCM_GLOBAL_VARS_INIT(static_write);
#endif

    scm_register_funcs(scm_functable_r5rs_write);

    /* To allow re-initialization of the interpreter, this variable must be
     * re-initialized by assignment. Initialized .data section does not work
     * for such situation.  -- YamaKen 2006-03-31 */
    scm_write_ss_func = scm_write;
}

SCM_EXPORT void
scm_write(ScmObj port, ScmObj obj)
{
    write_internal(port, obj, AS_WRITE);
}

SCM_EXPORT void
scm_display(ScmObj port, ScmObj obj)
{
    write_internal(port, obj, AS_DISPLAY);
}

static void
write_internal(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    DECLARE_INTERNAL_FUNCTION("write");

    ENSURE_PORT(port);
    SCM_ENSURE_LIVE_PORT(port);
    if (!(SCM_PORT_FLAG(port) & SCM_PORTFLAG_OUTPUT))
        ERR_OBJ("output port required but got", port);

    write_obj(port, obj, otype);
    scm_port_flush(port);
}

static void
write_obj(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    ScmObj sym;

#if SCM_USE_SRFI38
    if (INTERESTINGP(obj)) {
        scm_intobj_t index = get_shared_index(obj);
        if (index > 0) {
            /* defined datum */
            scm_format(port, SCM_FMT_RAW_C, "#~ZU#", (size_t)index);
            return;
        }
        if (index < 0) {
            /* defining datum, with the new index negated */
            scm_format(port, SCM_FMT_RAW_C, "#~ZU=", (size_t)-index);
            /* Print it; the next time it'll be defined. */
        }
    }
#endif
    switch (SCM_TYPE(obj)) {
#if SCM_USE_INT
    case ScmInt:
        scm_format(port, SCM_FMT_RAW_C, "~MD", SCM_INT_VALUE(obj));
        break;
#endif
    case ScmCons:
        if (ERROBJP(obj))
            write_errobj(port, obj, otype);
        else
            write_list(port, obj, otype);
        break;
    case ScmSymbol:
        scm_port_puts(port, SCM_SYMBOL_NAME(obj));
        break;
#if SCM_USE_CHAR
    case ScmChar:
        write_char(port, obj, otype);
        break;
#endif
#if SCM_USE_STRING
    case ScmString:
        write_string(port, obj, otype);
        break;
#endif
    case ScmFunc:
        scm_port_puts(port, (SCM_SYNTAXP(obj)) ? "#<syntax " : "#<subr ");
        sym = scm_symbol_bound_to(obj);
        if (TRUEP(sym))
            scm_display(port, sym);
        else
            scm_format(port, SCM_FMT_RAW_C, "~P", (void *)obj);
        scm_port_put_char(port, '>');
        break;
#if SCM_USE_HYGIENIC_MACRO
    case ScmMacro:
        scm_port_puts(port, "#<macro ");
        write_obj(port, SCM_HMACRO_RULES(obj), otype);
        scm_port_puts(port, ">");
        break;
    case ScmFarsymbol:
        write_farsymbol(port, obj, otype);
        break;
    case ScmSubpat:
        if (SCM_SUBPAT_PVARP(obj)) {
#if SCM_DEBUG_MACRO
            scm_port_puts(port, "#<pvar ");
            write_obj(port, SCM_SUBPAT_OBJ(obj), otype);
            scm_format(port, SCM_FMT_RAW_C, " ~MD>",
                       SCM_SUBPAT_PVAR_INDEX(obj));
#else  /* not SCM_DEBUG_MACRO */
            write_obj(port, SCM_SUBPAT_OBJ(obj), otype);
#endif /* not SCM_DEBUG_MACRO */
        } else {
            SCM_ASSERT(SCM_SUBPAT_REPPATP(obj));
            write_obj(port, SCM_SUBPAT_REPPAT_PAT(obj), otype);
#if SCM_DEBUG_MACRO
            scm_format(port, SCM_FMT_RAW_C, " ..[~MD]..",
                       SCM_SUBPAT_REPPAT_PVCOUNT(obj));
#else
            scm_port_puts(port, " ...");
#endif
        }
        break;
#endif /* SCM_USE_HYGIENIC_MACRO */
    case ScmClosure:
#if SCM_USE_LEGACY_MACRO
        if (SYNTACTIC_CLOSUREP(obj))
            scm_port_puts(port, "#<syntactic closure ");
        else
#endif
            scm_port_puts(port, "#<closure ");
        write_obj(port, SCM_CLOSURE_EXP(obj), otype);
        scm_port_put_char(port, '>');
        break;
#if SCM_USE_VECTOR
    case ScmVector:
        write_vector(port, obj, otype);
        break;
#endif
    case ScmPort:
        write_port(port, obj, otype);
        break;
#if SCM_USE_CONTINUATION
    case ScmContinuation:
        scm_format(port, SCM_FMT_RAW_C, "#<continuation ~P>", (void *)obj);
        break;
#endif
    case ScmValuePacket:
        scm_port_puts(port, "#<values ");
        write_obj(port, SCM_VALUEPACKET_VALUES(obj), otype);
#if SCM_USE_VALUECONS
#if SCM_USE_STORAGE_FATTY
        /* SCM_VALUEPACKET_VALUES() changes the type destructively */
        SCM_ENTYPE(obj, ScmValuePacket);
#else /* SCM_USE_STORAGE_FATTY */
#error "valuecons is not supported on this storage implementation"
#endif /* SCM_USE_STORAGE_FATTY */
#endif /* SCM_USE_VALUECONS */
        scm_port_put_char(port, '>');
        break;
    case ScmConstant:
        write_constant(port, obj, otype);
        break;
#if SCM_USE_SSCM_EXTENSIONS
    case ScmCPointer:
        scm_format(port, SCM_FMT_RAW_C,
                   "#<c_pointer ~P>", SCM_C_POINTER_VALUE(obj));
        break;
    case ScmCFuncPointer:
        scm_format(port, SCM_FMT_RAW_C,
                   "#<c_func_pointer ~P>",
                   (void *)(uintptr_t)SCM_C_FUNCPOINTER_VALUE(obj));
        break;
#endif

    case ScmRational:
    case ScmReal:
    case ScmComplex:
    default:
        SCM_NOTREACHED;
    }
}

#if SCM_USE_CHAR
static void
write_char(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    const ScmSpecialCharInfo *info;
    scm_ichar_t c;

    c = SCM_CHAR_VALUE(obj);
    switch (otype) {
    case AS_WRITE:
        scm_port_puts(port, "#\\");
        /* special chars */
        for (info = scm_special_char_table; info->esc_seq; info++) {
            if (c == info->code) {
                scm_port_puts(port, info->lex_rep);
                return;
            }
        }

        /* other control chars are printed in hexadecimal form */
        if (ICHAR_CONTROLP(c)) {
            scm_format(port, SCM_FMT_RAW_C, "x~02MX", (scm_int_t)c);
            return;
        }
        /* FALLTHROUGH */
    case AS_DISPLAY:
        scm_port_put_char(port, c);
        break;

    default:
        SCM_NOTREACHED;
    }
}
#endif /* SCM_USE_CHAR */

#if SCM_USE_STRING
static void
write_string(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
#if SCM_USE_MULTIBYTE_CHAR
    ScmCharCodec *codec;
    ScmMultibyteString mbs;
    size_t len;
#else
    scm_int_t i, len;
#endif
    const ScmSpecialCharInfo *info;
    const char *str;
    scm_ichar_t c;
    DECLARE_INTERNAL_FUNCTION("write");

    str = SCM_STRING_STR(obj);

    switch (otype) {
    case AS_WRITE:
        scm_port_put_char(port, '\"'); /* opening doublequote */
#if SCM_USE_MULTIBYTE_CHAR
        if (scm_current_char_codec != scm_port_codec(port)) {
            /* Since the str does not have its encoding information, here
             * assumes that scm_current_char_codec is that. And then SigScheme
             * does not have an encoding conversion mechanism, puts it
             * as-is. */
            scm_port_puts(port, str);
        } else {
            len = strlen(str);
            codec = scm_port_codec(port);
            SCM_MBS_INIT2(mbs, str, len);
            while (SCM_MBS_GET_SIZE(mbs)) {
                c = SCM_CHARCODEC_READ_CHAR(codec, mbs);
#else /* SCM_USE_MULTIBYTE_CHAR */
            len = SCM_STRING_LEN(obj);
            for (i = 0; i < len; i++) {
                c = str[i];
#endif /* SCM_USE_MULTIBYTE_CHAR */
                for (info = scm_special_char_table; info->esc_seq; info++) {
                    if (c == info->code) {
                        scm_port_puts(port, info->esc_seq);
                        goto continue2;
                    }
                }
                scm_port_put_char(port, c);
            continue2:
                ;
            }
#if SCM_USE_MULTIBYTE_CHAR
        }
#endif
        scm_port_put_char(port, '\"'); /* closing doublequote */
        break;

    case AS_DISPLAY:
        scm_port_puts(port, str);
        break;

    default:
        SCM_NOTREACHED;
    }
}
#endif /* SCM_USE_STRING */

static void
write_list(ScmObj port, ScmObj lst, enum ScmOutputType otype)
{
    ScmObj car;
#if SCM_USE_SRFI38
    size_t necessary_close_parens;
    scm_intobj_t index;
#endif
    DECLARE_INTERNAL_FUNCTION("write");

#if SCM_USE_SRFI38
    necessary_close_parens = 1;
  cheap_recursion:
#endif

    SCM_ASSERT(CONSP(lst));

    scm_port_put_char(port, '(');

    FOR_EACH (car, lst) {
        write_obj(port, car, otype);
        if (!CONSP(lst))
            break;
        scm_port_put_char(port, ' ');

#if SCM_USE_SRFI38
        /* See if the next pair is shared.  Note that the case
         * where the first pair is shared is handled in
         * write_obj(). */
        index = get_shared_index(lst);
        if (index > 0) {
            /* defined datum */
            scm_format(port, SCM_FMT_RAW_C, ". #~ZU#", (size_t)index);
            goto close_parens_and_return;
        }
        if (index < 0) {
            /* defining datum, with the new index negated */
            scm_format(port, SCM_FMT_RAW_C, ". #~ZU=", (size_t)-index);
            necessary_close_parens++;
            goto cheap_recursion;
        }
#endif
    }

    /* last item */
    if (!NULLP(lst)) {
        scm_port_puts(port, " . ");
        /* Callee takes care of shared data. */
        write_obj(port, lst, otype);
    }

#if SCM_USE_SRFI38
  close_parens_and_return:
    while (necessary_close_parens--)
#endif
        scm_port_put_char(port, ')');
}

#if SCM_USE_VECTOR
static void
write_vector(ScmObj port, ScmObj vec, enum ScmOutputType otype)
{
    ScmObj *v;
    scm_int_t len, i;

    scm_port_puts(port, "#(");

    v = SCM_VECTOR_VEC(vec);
    len = SCM_VECTOR_LEN(vec);
    for (i = 0; i < len; i++) {
        if (i)
            scm_port_put_char(port, ' ');
        write_obj(port, v[i], otype);
    }

    scm_port_put_char(port, ')');
}
#endif /* SCM_USE_VECTOR */

static void
write_port(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    char *info;

    scm_port_puts(port, "#<");

    /* input or output */
    /* print "iport", "oport" or "ioport" if bidirectional port */
    if (SCM_PORT_FLAG(obj) & SCM_PORTFLAG_INPUT)
        scm_port_put_char(port, 'i');
    if (SCM_PORT_FLAG(obj) & SCM_PORTFLAG_OUTPUT)
        scm_port_put_char(port, 'o');
    scm_port_puts(port, "port");

    /* file or string */
    info = scm_port_inspect(obj);
    if (*info) {
        scm_port_put_char(port, ' ');
        scm_port_puts(port, info);
    }
    free(info);

    scm_port_put_char(port, '>');
}

static void
write_constant(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    const char *str;

    if (EQ(obj, SCM_NULL))
        str = "()";
    else if (EQ(obj, SCM_TRUE))
        str = "#t";
    else if (EQ(obj, SCM_FALSE))
        str = "#f";
    else if (EQ(obj, SCM_EOF))
        str = "#<eof>";
    else if (EQ(obj, SCM_UNBOUND))
        str = "#<unbound>";
    else if (EQ(obj, SCM_UNDEF))
        str = "#<undef>";
    else
        SCM_NOTREACHED;

    scm_port_puts(port, str);
}

static void
write_errobj(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    ScmObj reason, objs, elm;
    DECLARE_INTERNAL_FUNCTION("write");

    MUST_POP_ARG(obj);
    reason      = MUST_POP_ARG(obj);
    objs        = MUST_POP_ARG(obj);
    MUST_POP_ARG(obj);
    ASSERT_NO_MORE_ARG(obj);

    switch (otype) {
    case AS_WRITE:
        scm_port_puts(port, "#<error ");
        scm_write(port, reason);
        break;

    case AS_DISPLAY:
        scm_display(port, reason);
        break;

    default:
        SCM_NOTREACHED;
    }

    FOR_EACH (elm, objs) {
        scm_port_put_char(port, ' ');
        scm_write(port, elm);
    }

    if (otype == AS_WRITE)
        scm_port_put_char(port, '>');
}

#if SCM_USE_HYGIENIC_MACRO
static void
write_farsymbol(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    /* Assumes that ScmPackedEnv is an integer. */
    scm_port_puts(port, "#<farsym");
    for (; SCM_FARSYMBOLP(obj); obj = SCM_FARSYMBOL_SYM(obj))
        scm_format(port, SCM_FMT_RAW_C, " ~MD ", SCM_FARSYMBOL_ENV(obj));
    scm_display(port, obj); /* Name. */
    scm_port_puts(port, ">");
}
#endif /* SCM_USE_HYGIENIC_MACRO */

#if SCM_USE_SRFI38
static void
hash_grow(scm_hash_table *tab)
{
    size_t old_size, new_size, i;
    scm_hash_entry *old_ents;

    old_size = tab->size;
    new_size = old_size * 2;
    old_ents = tab->ents;

    tab->ents = scm_malloc(new_size * sizeof(scm_hash_entry));
    tab->size = new_size;
    tab->used = 0;
    for (i = 0; i < new_size; i++)
        tab->ents[i].key = SCM_INVALID;

    for (i = 0; i < old_size; i++)
        hash_lookup(tab, old_ents[i].key, old_ents[i].datum, HASH_INSERT);

    free(old_ents);
}

/**
 * @return A pointer to the entry, or NULL if not found.
 */
static scm_hash_entry *
hash_lookup(scm_hash_table *tab, ScmObj key, scm_intobj_t datum, int flag)
{
    size_t i;
    hashval_t hashval;
    scm_hash_entry *ent;

    /* If we have > 32 bits, we'll discard some of them.  The lower
     * bits are zeroed for alignment or used for tag bits, and in the
     * latter case, the tag can only take 3 values: pair, string, or
     * vector.  We'll drop these bits.  KEYs are expected to be
     * pointers into the heap, so their higher bis are probably
     * uniform.  I haven't confirmed either's validity, though. */
    hashval = (hashval_t)key;
    if (sizeof(hashval) > 4) {
        hashval /= sizeof(ScmCell);
        hashval &= 0xffffffff;
    }

    hashval *= 2654435761UL; /* golden ratio hash */

    /* We probe linearly, since a) speed isn't a primary concern for
     * SigScheme, and b) having a table of primes only for this
     * purpose is probably just a waste. */
    for (i = 0; i < tab->size; i++) {
        ent = &(tab->ents)[(hashval + i) & (tab->size - 1)];
        if (!OCCUPIED(ent)) {
            if (flag & HASH_INSERT) {
                ent->key = key;
                ent->datum = datum;
                tab->used++;

                /* used > size * 2/3 --> overpopulated */
                if (tab->used * 3 > tab->size * 2)
                    hash_grow(tab);
            }
            return NULL;
        }
        if (EQ(ent->key, key))
            return ent;
    }

    /* A linear probe should always find a slot. */
    SCM_NOTREACHED;
}

/**
 * Find out what non-atomic objects a structure shares within itself.
 * @param obj The object in question, or a part of it.
 * @param ctx Where to put the scan results.
 */
static void
write_ss_scan(ScmObj obj, scm_write_ss_context *ctx)
{
#if SCM_USE_VECTOR
    scm_int_t i, len;
#endif
    scm_hash_entry *ent;
    ScmObj reason, objs;
    DECLARE_INTERNAL_FUNCTION("write-with-shared-structure");

    if (ERROBJP(obj)) {
        MUST_POP_ARG(obj);
        reason      = MUST_POP_ARG(obj);
        objs        = MUST_POP_ARG(obj);
        MUST_POP_ARG(obj);
        ASSERT_NO_MORE_ARG(obj);

        write_ss_scan(reason, ctx);
        write_ss_scan(objs, ctx);
        return;
    }

    /* (for-each mark-as-seen-or-return-if-familiar obj) */
    for (; CONSP(obj); obj = CDR(obj)) {
        ent = hash_lookup(&ctx->seen, obj, NONDEFINING_DATUM, HASH_INSERT);
        if (ent) {
            ent->datum = DEFINING_DATUM;
            return;
        }
        write_ss_scan(CAR(obj), ctx);
    }

    if (INTERESTINGP(obj)) {
        ent = hash_lookup(&ctx->seen, obj, NONDEFINING_DATUM, HASH_INSERT);
        if (ent) {
            ent->datum = DEFINING_DATUM;
            return;
        }
        switch (SCM_TYPE(obj)) {
        case ScmClosure:
            /* We don't need to track env because it's not printed anyway. */
            write_ss_scan(SCM_CLOSURE_EXP(obj), ctx);
            break;

        case ScmValuePacket:
#if SCM_USE_VALUECONS
#if SCM_USE_STORAGE_FATTY
            if (!SCM_NULLVALUESP(obj)) {
                /* EQ(obj, SCM_VALUEPACKET_VALUES(obj)) */
                write_ss_scan(CDR(SCM_VALUEPACKET_VALUES(obj)), ctx);
                /* SCM_VALUEPACKET_VALUES() changes the type destructively */
                SCM_ENTYPE(obj, ScmValuePacket);
            }
#else /* SCM_USE_STORAGE_FATTY */
#error "valuecons is not supported on this storage implementation"
#endif /* SCM_USE_STORAGE_FATTY */
#else /* SCM_USE_VALUECONS */
            write_ss_scan(SCM_VALUEPACKET_VALUES(obj), ctx);
#endif /* SCM_USE_VALUECONS */
            break;

#if SCM_USE_VECTOR
        case ScmVector:
            for (i = 0, len = SCM_VECTOR_LEN(obj); i < len; i++)
                write_ss_scan(SCM_VECTOR_VEC(obj)[i], ctx);
            break;
#endif /* SCM_USE_VECTOR */

        default:
            break;
        }
    }
}

/**
 * @return The index for obj, if it's a defined datum.  If it's a
 *         defining datum, allocate an index for it and return the
 *         *additive inverse* of the index.  If obj is nondefining,
 *         return zero.
 */
static scm_intobj_t
get_shared_index(ScmObj obj)
{
    scm_hash_entry *ent;

    if (l_write_ss_ctx) {
        ent = hash_lookup(&l_write_ss_ctx->seen, obj, 0, HASH_FIND);

        if (ent) {
            if (ent->datum == DEFINING_DATUM) {
                ent->datum = l_write_ss_ctx->next_index++;
                return -(ent->datum);
            }
            return ent->datum;
        }
    }
    return 0;
}

static void
write_ss_internal(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    scm_write_ss_context ctx = {{0}};
    size_t i;

    ctx.next_index = 1;
    ctx.seen.size = 1 << 8; /* arbitrary initial size */
    ctx.seen.ents = scm_malloc(ctx.seen.size * sizeof(scm_hash_entry));
    for (i = 0; i < ctx.seen.size; i++)
        ctx.seen.ents[i].key = SCM_INVALID;

    write_ss_scan(obj, &ctx);

    /* If no structure is shared, we do a normal write. */
    if (!HASH_EMPTY(ctx.seen))
        l_write_ss_ctx = &ctx;

    write_internal(port, obj, otype);

    l_write_ss_ctx = NULL;
    free(ctx.seen.ents);
}

/* write with shared structure */
SCM_EXPORT void
scm_write_ss(ScmObj port, ScmObj obj)
{
    write_ss_internal(port, obj, AS_WRITE);
}

SCM_EXPORT void
scm_display_errobj_ss(ScmObj port, ScmObj errobj)
{
    write_ss_internal(port, errobj, AS_DISPLAY);
}
#endif /* SCM_USE_SRFI38 */

/*===========================================================================
  R5RS : 6.6 Input and Output : 6.6.3 Output
===========================================================================*/
SCM_EXPORT ScmObj
scm_p_write(ScmObj obj, ScmObj args)
{
    ScmObj port;
    DECLARE_FUNCTION("write", procedure_variadic_1);

    port = scm_prepare_port(args, scm_out);
    scm_write(port, obj);
    return SCM_UNDEF;
}

SCM_EXPORT ScmObj
scm_p_display(ScmObj obj, ScmObj args)
{
    ScmObj port;
    DECLARE_FUNCTION("display", procedure_variadic_1);

    port = scm_prepare_port(args, scm_out);
    scm_display(port, obj);
    return SCM_UNDEF;
}
