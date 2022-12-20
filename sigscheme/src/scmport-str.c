/*===========================================================================
 *  Filename : scmport-str.c
 *  About    : A ScmBytePort implementation for string
 *
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

/*
 * - This file is intended to be portable. Don't depend on SigScheme.
 * - To isolate and hide implementation-dependent things, don't merge this file
 *   into another
 */

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scmint.h"
#include "scmport-config.h"
#include "scmport.h"
#include "scmport-str.h"

/*=======================================
  File Local Macro Definitions
=======================================*/

/*=======================================
  File Local Type Definitions
=======================================*/
typedef struct ScmInputStrPort_  ScmInputStrPort;
typedef struct ScmOutputStrPort_ ScmOutputStrPort;

struct ScmInputStrPort_ {  /* inherits ScmBytePort */
    const ScmBytePortVTbl *vptr;

    scm_byte_t *str;
    const scm_byte_t *cur;
    scm_bool has_str_ownership;
    void *opaque;  /* client-specific opaque information */
    ScmInputStrPort_finalizer finalize;
};

struct ScmOutputStrPort_ {  /* inherits ScmBytePort */
    const ScmBytePortVTbl *vptr;

    scm_byte_t *str;
    size_t cur;       /* offset to terminal '\0' */
    size_t buf_size;
    void *opaque;     /* client-specific opaque information */
    ScmOutputStrPort_finalizer finalize;
};

/*=======================================
  File Local Function Declarations
=======================================*/
/* input port */
static ScmBytePort *istrport_new(scm_byte_t *str, scm_bool ownership,
                                 ScmInputStrPort_finalizer finalize);
static void istrport_finalize(char **str, scm_bool ownership, void **opaque);

static ScmBytePort *istrport_dyn_cast(ScmBytePort *bport,
                                      const ScmBytePortVTbl *dest_vptr);
static void istrport_close(ScmInputStrPort *port);
static char *istrport_inspect(ScmInputStrPort *port);
static scm_ichar_t istrport_get_byte(ScmInputStrPort *port);
static scm_ichar_t istrport_peek_byte(ScmInputStrPort *port);
static scm_bool istrport_byte_readyp(ScmInputStrPort *port);
static void istrport_puts(ScmInputStrPort *port, const char *str);
static void istrport_write(ScmInputStrPort *port,
                           size_t nbytes, const char *buf);
static void istrport_flush(ScmInputStrPort *port);

/* output port */
static void ostrport_finalize(char **str, size_t buf_size, void **opaque);

static ScmBytePort *ostrport_dyn_cast(ScmBytePort *bport,
                                      const ScmBytePortVTbl *dest_vptr);
static void ostrport_close(ScmOutputStrPort *port);
static char *ostrport_inspect(ScmOutputStrPort *port);
static scm_ichar_t ostrport_get_byte(ScmOutputStrPort *port);
static scm_ichar_t ostrport_peek_byte(ScmOutputStrPort *port);
static scm_bool ostrport_byte_readyp(ScmOutputStrPort *port);
static void ostrport_puts(ScmOutputStrPort *port, const char *str);
static void ostrport_write(ScmOutputStrPort *port,
                           size_t nbytes, const char *buf);
static void ostrport_flush(ScmOutputStrPort *port);

static void ostrport_append(ScmOutputStrPort *port,
                            size_t len, const scm_byte_t *str);

/*=======================================
  Variable Definitions
=======================================*/
static const ScmBytePortVTbl ScmInputStrPort_vtbl = {
    (ScmBytePortMethod_dyn_cast)   &istrport_dyn_cast,
    (ScmBytePortMethod_close)      &istrport_close,
    (ScmBytePortMethod_inspect)    &istrport_inspect,
    (ScmBytePortMethod_get_byte)   &istrport_get_byte,
    (ScmBytePortMethod_peek_byte)  &istrport_peek_byte,
    (ScmBytePortMethod_byte_readyp)&istrport_byte_readyp,
    (ScmBytePortMethod_puts)       &istrport_puts,
    (ScmBytePortMethod_write)      &istrport_write,
    (ScmBytePortMethod_flush)      &istrport_flush
};
SCM_EXPORT const ScmBytePortVTbl *const ScmInputStrPort_vptr
    = &ScmInputStrPort_vtbl;

static const ScmBytePortVTbl ScmOutputStrPort_vtbl = {
    (ScmBytePortMethod_dyn_cast)   &ostrport_dyn_cast,
    (ScmBytePortMethod_close)      &ostrport_close,
    (ScmBytePortMethod_inspect)    &ostrport_inspect,
    (ScmBytePortMethod_get_byte)   &ostrport_get_byte,
    (ScmBytePortMethod_peek_byte)  &ostrport_peek_byte,
    (ScmBytePortMethod_byte_readyp)&ostrport_byte_readyp,
    (ScmBytePortMethod_puts)       &ostrport_puts,
    (ScmBytePortMethod_write)      &ostrport_write,
    (ScmBytePortMethod_flush)      &ostrport_flush
};
SCM_EXPORT const ScmBytePortVTbl *const ScmOutputStrPort_vptr
    = &ScmOutputStrPort_vtbl;

/*=======================================
  Function Definitions
=======================================*/

/*
 * Client code must call this first even if current implementation does not
 * contain actual code.
 */
SCM_EXPORT void
scm_strport_init(void)
{
}

static ScmBytePort *
istrport_new(scm_byte_t *str, scm_bool ownership,
             ScmInputStrPort_finalizer finalize)
{
    ScmInputStrPort *port;

    SCM_PORT_ASSERT(str);

    port = SCM_PORT_MALLOC(sizeof(ScmInputStrPort));

    port->vptr = ScmInputStrPort_vptr;
    port->cur = port->str = str;
    port->has_str_ownership = ownership;
    port->opaque = NULL;
    port->finalize = (finalize) ? finalize : &istrport_finalize;

    return (ScmBytePort *)port;
}

SCM_EXPORT ScmBytePort *
ScmInputStrPort_new(char *str, ScmInputStrPort_finalizer finalize)
{
    return istrport_new((scm_byte_t *)str, scm_true, finalize);
}

SCM_EXPORT ScmBytePort *
ScmInputStrPort_new_copying(const char *str,
                            ScmInputStrPort_finalizer finalize)
{
    return istrport_new((scm_byte_t *)SCM_PORT_STRDUP(str),
                        scm_true, finalize);
}

SCM_EXPORT ScmBytePort *
ScmInputStrPort_new_const(const char *str, ScmInputStrPort_finalizer finalize)
{
    /* str is actually treated as const */
    return istrport_new((scm_byte_t *)str, scm_false, finalize);
}

SCM_EXPORT void **
ScmInputStrPort_ref_opaque(ScmBytePort *bport)
{
    ScmInputStrPort *port;

    port = SCM_BYTEPORT_DYNAMIC_CAST(ScmInputStrPort, bport);

    return &port->opaque;
}

static ScmBytePort *
istrport_dyn_cast(ScmBytePort *bport, const ScmBytePortVTbl *dst_vptr)
{
    return (dst_vptr == ScmInputStrPort_vptr) ? bport : NULL;
}

/* default finalizer */
static void
istrport_finalize(char **str, scm_bool ownership, void **opaque)
{
    if (ownership)
        free(*str);
}

static void
istrport_close(ScmInputStrPort *port)
{
    SCM_PORT_ASSERT(port->finalize);

    /* To suppress the "dereferencing type-punned pointer will break
     * strict-aliasing rules" warning on gcc, apply a reinterpret_cast
     * here. This operation is safe on the case.   -- YamaKen 2007-01-06 */
    (*port->finalize)((char **)(uintptr_t)&port->str,
                      port->has_str_ownership, &port->opaque);
    free(port);
}

static char *
istrport_inspect(ScmInputStrPort *port)
{
    return SCM_PORT_STRDUP("string");
}

static scm_ichar_t
istrport_get_byte(ScmInputStrPort *port)
{
    return (*port->cur) ? *port->cur++ : SCM_ICHAR_EOF;
}

static scm_ichar_t
istrport_peek_byte(ScmInputStrPort *port)
{
    return (*port->cur) ? *port->cur : SCM_ICHAR_EOF;
}

static scm_bool
istrport_byte_readyp(ScmInputStrPort *port)
{
    return scm_true;
}

static void
istrport_puts(ScmInputStrPort *port, const char *str)
{
    SCM_PORT_ERROR_INVALID_OPERATION(BYTE, port, ScmInputStrPort);
    /* NOTREACHED */
}

static void
istrport_write(ScmInputStrPort *port, size_t nbytes, const char *buf)
{
    SCM_PORT_ERROR_INVALID_OPERATION(BYTE, port, ScmInputStrPort);
    /* NOTREACHED */
}

static void
istrport_flush(ScmInputStrPort *port)
{
    SCM_PORT_ERROR_INVALID_OPERATION(BYTE, port, ScmInputStrPort);
    /* NOTREACHED */
}


SCM_EXPORT ScmBytePort *
ScmOutputStrPort_new(ScmOutputStrPort_finalizer finalize)
{
    ScmOutputStrPort *port;

    port = SCM_PORT_MALLOC(sizeof(ScmOutputStrPort));

    port->vptr = ScmOutputStrPort_vptr;
    port->str = NULL;
    port->cur = 0;
    port->buf_size = 0;
    port->opaque = NULL;
    port->finalize = (finalize) ? finalize : &ostrport_finalize;

    return (ScmBytePort *)port;
}

SCM_EXPORT const char *
ScmOutputStrPort_str(ScmBytePort *bport)
{
    ScmOutputStrPort *port;

    port = SCM_BYTEPORT_DYNAMIC_CAST(ScmOutputStrPort, bport);

    return (port->str) ? (const char *)port->str : "";
}

SCM_EXPORT size_t
ScmOutputStrPort_c_strlen(ScmBytePort *bport)
{
    ScmOutputStrPort *port;

    port = SCM_BYTEPORT_DYNAMIC_CAST(ScmOutputStrPort, bport);

    return (port->buf_size) ? port->buf_size - sizeof("") : 0;
}

SCM_EXPORT void **
ScmOutputStrPort_ref_opaque(ScmBytePort *bport)
{
    ScmOutputStrPort *port;

    port = SCM_BYTEPORT_DYNAMIC_CAST(ScmOutputStrPort, bport);

    return &port->opaque;
}

static ScmBytePort *
ostrport_dyn_cast(ScmBytePort *bport, const ScmBytePortVTbl *dst_vptr)
{
    return (dst_vptr == ScmOutputStrPort_vptr) ? bport : NULL;
}

static void
ostrport_finalize(char **str, size_t buf_size, void **opaque)
{
    free(*str);
}

static void
ostrport_close(ScmOutputStrPort *port)
{
    SCM_PORT_ASSERT(port->finalize);

    /* To suppress the "dereferencing type-punned pointer will break
     * strict-aliasing rules" warning on gcc, apply a reinterpret_cast
     * here. This operation is safe on the case.   -- YamaKen 2007-01-06 */
    (*port->finalize)((char **)(uintptr_t)&port->str,
                      port->buf_size, &port->opaque);
    free(port);
}

static char *
ostrport_inspect(ScmOutputStrPort *port)
{
    return SCM_PORT_STRDUP("string");
}

static scm_ichar_t
ostrport_get_byte(ScmOutputStrPort *port)
{
    SCM_PORT_ERROR_INVALID_OPERATION(BYTE, port, ScmOutputStrPort);
    /* NOTREACHED */
}

static scm_ichar_t
ostrport_peek_byte(ScmOutputStrPort *port)
{
    SCM_PORT_ERROR_INVALID_OPERATION(BYTE, port, ScmOutputStrPort);
    /* NOTREACHED */
}

static scm_bool
ostrport_byte_readyp(ScmOutputStrPort *port)
{
    SCM_PORT_ERROR_INVALID_OPERATION(BYTE, port, ScmOutputStrPort);
    /* NOTREACHED */
}

static void
ostrport_puts(ScmOutputStrPort *port, const char *str)
{
    ostrport_append(port, strlen(str), (const scm_byte_t *)str);
}

static void
ostrport_write(ScmOutputStrPort *port, size_t nbytes, const char *buf)
{
    ostrport_append(port, nbytes, (const scm_byte_t *)buf);
}

static void
ostrport_flush(ScmOutputStrPort *port)
{
}

static void
ostrport_append(ScmOutputStrPort *port, size_t len, const scm_byte_t *str)
{
    SCM_PORT_ASSERT(str);

    /* extend the buffer */
    if (port->buf_size - port->cur < len + sizeof("")) {
        if (!port->buf_size)
            port->buf_size = sizeof("");

        port->buf_size += len;
        port->str = SCM_PORT_REALLOC(port->str, port->buf_size);
    }

    memcpy(port->str + port->cur, str, len);
    port->cur += len;
    port->str[port->cur] = '\0';
}
