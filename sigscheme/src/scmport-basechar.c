/*===========================================================================
 *  Filename : scmport-basechar.c
 *  About    : ScmBaseCharPort implementation
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

/*=======================================
  File Local Macro Definitions
=======================================*/

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  File Local Function Declarations
=======================================*/
static ScmCharPort *basecport_dyn_cast(ScmCharPort *cport,
                                       const ScmCharPortVTbl *dst_vptr);
static void basecport_close(ScmBaseCharPort *port);
static ScmCharCodec *basecport_codec(ScmBaseCharPort *port);
static char *basecport_inspect(ScmBaseCharPort *port);
static scm_ichar_t basecport_get_char(ScmBaseCharPort *port);
static scm_ichar_t basecport_peek_char(ScmBaseCharPort *port);
static scm_bool basecport_char_readyp(ScmBaseCharPort *port);
static void basecport_puts(ScmBaseCharPort *port, const char *str);
static void basecport_put_char(ScmBaseCharPort *port, scm_ichar_t ch);
static void basecport_flush(ScmBaseCharPort *port);

/*=======================================
  Variable Definitions
=======================================*/
static const ScmCharPortVTbl ScmBaseCharPort_vtbl = {
    (ScmCharPortMethod_dyn_cast)   &basecport_dyn_cast,
    (ScmCharPortMethod_close)      &basecport_close,
    (ScmCharPortMethod_codec)      &basecport_codec,
    (ScmCharPortMethod_inspect)    &basecport_inspect,
    (ScmCharPortMethod_get_char)   &basecport_get_char,
    (ScmCharPortMethod_peek_char)  &basecport_peek_char,
    (ScmCharPortMethod_char_readyp)&basecport_char_readyp,
    (ScmCharPortMethod_puts)       &basecport_puts,
    (ScmCharPortMethod_put_char)   &basecport_put_char,
    (ScmCharPortMethod_flush)      &basecport_flush
};
SCM_EXPORT const ScmCharPortVTbl *const ScmBaseCharPort_vptr
    = &ScmBaseCharPort_vtbl;

/*=======================================
  Function Definitions
=======================================*/
SCM_EXPORT void
ScmBaseCharPort_construct(ScmBaseCharPort *port, const ScmCharPortVTbl *vptr,
                          ScmBytePort *bport)
{
    port->vptr = vptr;
    port->bport = bport;
#if SCM_DEBUG
    port->linenum = 1;
#else
    port->linenum = 0;
#endif
}

SCM_EXPORT char *
ScmBaseCharPort_inspect(ScmBaseCharPort *port, const char *header)
{
    const char *encoding;
    char *bport_part, *combined;
    size_t size;

    encoding = SCM_CHARPORT_ENCODING((ScmCharPort *)port);
    bport_part = SCM_BYTEPORT_INSPECT((ScmBytePort *)port->bport);
    size = strlen(header) + strlen(encoding) + strlen(bport_part)
        + sizeof("  ");
    combined = SCM_PORT_MALLOC(size);
    sprintf(combined, "%s %s %s", header, encoding, bport_part);
    free(bport_part);

    return combined;
}

SCM_EXPORT size_t
ScmBaseCharPort_line_number(ScmBaseCharPort *port)
{
    return port->linenum;
}

static ScmCharPort *
basecport_dyn_cast(ScmCharPort *cport, const ScmCharPortVTbl *dst_vptr)
{
    return (dst_vptr == ScmBaseCharPort_vptr) ? cport : NULL;
}

static void
basecport_close(ScmBaseCharPort *port)
{
    SCM_BYTEPORT_CLOSE(port->bport);
    free(port);
}

static ScmCharCodec *
basecport_codec(ScmBaseCharPort *port)
{
    SCM_PORT_ERROR_INVALID_OPERATION(CHAR, port, ScmBaseCharPort);
    /* NOTREACHED */
}

static char *
basecport_inspect(ScmBaseCharPort *port)
{
    return ScmBaseCharPort_inspect(port, "unknown");
}

static scm_ichar_t
basecport_get_char(ScmBaseCharPort *port)
{
    scm_ichar_t ch;

    ch = SCM_BYTEPORT_GET_BYTE(port->bport);
#if SCM_DEBUG
    if (ch == SCM_NEWLINE_STR[0])
        port->linenum++;
#endif

    return ch;
}

static scm_ichar_t
basecport_peek_char(ScmBaseCharPort *port)
{
    return SCM_BYTEPORT_PEEK_BYTE(port->bport);
}

static scm_bool
basecport_char_readyp(ScmBaseCharPort *port)
{
    return SCM_BYTEPORT_BYTE_READYP(port->bport);
}

static void
basecport_puts(ScmBaseCharPort *port, const char *str)
{
    SCM_BYTEPORT_PUTS(port->bport, str);
}

static void
basecport_put_char(ScmBaseCharPort *port, scm_ichar_t ch)
{
    SCM_PORT_ERROR_INVALID_OPERATION(CHAR, port, ScmBaseCharPort);
    /* NOTREACHED */
}

static void
basecport_flush(ScmBaseCharPort *port)
{
    SCM_BYTEPORT_FLUSH(port->bport);
}
