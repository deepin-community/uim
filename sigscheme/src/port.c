/*===========================================================================
 *  Filename : port.c
 *  About    : R5RS ports
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

#include <stddef.h>
#include <stdio.h>

#include "sigscheme.h"
#include "sigschemeinternal.h"
#if SCM_USE_MULTIBYTE_CHAR
#include "scmport-mbchar.h"
#else /* SCM_USE_MULTIBYTE_CHAR */
#include "scmport-sbchar.h"
#endif /* SCM_USE_MULTIBYTE_CHAR */
#include "scmport-file.h"

/*=======================================
  File Local Macro Definitions
=======================================*/
#define ERRMSG_CANNOT_OPEN_FILE "cannot open file"

#if !SCM_USE_CHAR
#define scm_p_read_char   NULL
#define scm_p_peek_char   NULL
#define scm_p_char_readyp NULL
#define scm_p_write_char  NULL
#endif

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  Variable Definitions
=======================================*/
#include "functable-r5rs-port.c"

SCM_DEFINE_EXPORTED_VARS(port);

#if (SCM_USE_READER || SCM_USE_WRITER)
SCM_EXPORT const ScmSpecialCharInfo scm_special_char_table[] = {
    /* printable characters */
    {'\"',   "\\\"",  "\""},         /* 34, R5RS */
    {'\\',   "\\\\",  "\\"},         /* 92, R5RS */
    {' ',    " ",     "space"},      /* 32, R5RS */

    /* control characters */
    {'\n',   "\\n",   "newline"},    /*  10, R5RS */
#if SCM_USE_R6RS_NAMED_CHARS
    {'\0',   "\\x00", "nul"},        /*   0 */
    {'\a',   "\\a",   "alarm"},      /*   7 */
    {'\b',   "\\b",   "backspace"},  /*   8 */
    {'\t',   "\\t",   "tab"},        /*   9 */
    {'\n',   "\\n",   "linefeed"},   /*  10 */
    {'\v',   "\\v",   "vtab"},       /*  11 */
    {'\f',   "\\f",   "page"},       /*  12 */
    {'\r',   "\\r",   "return"},     /*  13 */
    {0x1b,   "\\x1b", "esc"},        /*  27 */
    {0x7f,   "\\x7f", "delete"},     /* 127 */
#endif /* SCM_USE_R6RS_NAMED_CHARS */
    {0, NULL, NULL}
};
#endif /* (SCM_USE_READER || SCM_USE_WRITER) */

/*=======================================
  File Local Function Declarations
=======================================*/

/*=======================================
  Function Definitions
=======================================*/
SCM_EXPORT void
scm_init_port(void)
{
    SCM_GLOBAL_VARS_INIT(port);

    scm_register_funcs(scm_functable_r5rs_port);

#if !SCM_USE_CHAR
    SCM_SYMBOL_SET_VCELL(scm_intern("read-char"), SCM_UNBOUND);
    SCM_SYMBOL_SET_VCELL(scm_intern("peek-char"), SCM_UNBOUND);
    SCM_SYMBOL_SET_VCELL(scm_intern("char-ready?"), SCM_UNBOUND);
    SCM_SYMBOL_SET_VCELL(scm_intern("write-char"), SCM_UNBOUND);
#endif

    scm_fileport_init();
#if SCM_USE_MULTIBYTE_CHAR
    scm_mbcport_init();
#else
    scm_sbcport_init();
#endif

    scm_gc_protect_with_init(&scm_in,
                             scm_make_shared_file_port(stdin, "stdin",
                                                       SCM_PORTFLAG_INPUT));
    scm_gc_protect_with_init(&scm_out,
                             scm_make_shared_file_port(stdout, "stdout",
                                                       SCM_PORTFLAG_OUTPUT));
    scm_gc_protect_with_init(&scm_err,
                             scm_make_shared_file_port(stderr, "stderr",
                                                       SCM_PORTFLAG_OUTPUT));
}

SCM_EXPORT ScmObj
scm_prepare_port(ScmObj args, ScmObj default_port)
{
    ScmObj port;
    DECLARE_INTERNAL_FUNCTION("prepare_port");

    ASSERT_PROPER_ARG_LIST(args);

    if (NULLP(args)) {
        port = default_port;
    } else {
        port = POP(args);
        ASSERT_NO_MORE_ARG(args);
        ENSURE_PORT(port);
    }

    return port;
}

SCM_EXPORT ScmCharPort *
scm_make_char_port(ScmBytePort *bport)
{
#if  SCM_USE_MULTIBYTE_CHAR
    return ScmMultiByteCharPort_new(bport, scm_current_char_codec);
#else
    return ScmSingleByteCharPort_new(bport);
#endif
}

SCM_EXPORT ScmObj
scm_make_shared_file_port(FILE *file, const char *aux_info,
                          enum ScmPortFlag flag)
{
    ScmBytePort *bport;
    ScmCharPort *cport;

    bport = ScmFilePort_new_shared(file, aux_info);
    cport = scm_make_char_port(bport);
    return MAKE_PORT(cport, flag);
}

SCM_EXPORT void
scm_port_newline(ScmObj port)
{
    scm_port_puts(port, SCM_NEWLINE_STR);
    scm_port_flush(port);  /* required */
}

SCM_EXPORT void
scm_port_close(ScmObj port)
{
    SCM_ASSERT(SCM_PORTP(port));
    SCM_ASSERT(SCM_PORT_IMPL(port));

    SCM_CHARPORT_CLOSE(SCM_PORT_IMPL(port));
    SCM_PORT_SET_IMPL(port, NULL);
}

SCM_EXPORT ScmCharCodec *
scm_port_codec(ScmObj port)
{
    SCM_ENSURE_LIVE_PORT(port);
    return SCM_CHARPORT_CODEC(SCM_PORT_IMPL(port));
}

SCM_EXPORT char *
scm_port_inspect(ScmObj port)
{
    SCM_ENSURE_LIVE_PORT(port);
    return SCM_CHARPORT_INSPECT(SCM_PORT_IMPL(port));
}

SCM_EXPORT scm_ichar_t
scm_port_get_char(ScmObj port)
{
    SCM_ENSURE_LIVE_PORT(port);
    return SCM_CHARPORT_GET_CHAR(SCM_PORT_IMPL(port));
}

SCM_EXPORT scm_ichar_t
scm_port_peek_char(ScmObj port)
{
    SCM_ENSURE_LIVE_PORT(port);
    return SCM_CHARPORT_PEEK_CHAR(SCM_PORT_IMPL(port));
}

SCM_EXPORT scm_bool
scm_port_char_readyp(ScmObj port)
{
    SCM_ENSURE_LIVE_PORT(port);
    return SCM_CHARPORT_CHAR_READYP(SCM_PORT_IMPL(port));
}

SCM_EXPORT void
scm_port_puts(ScmObj port, const char *str)
{
    SCM_ENSURE_LIVE_PORT(port);
    SCM_CHARPORT_PUTS(SCM_PORT_IMPL(port), str);
}

SCM_EXPORT void
scm_port_put_char(ScmObj port, scm_ichar_t ch)
{
    SCM_ENSURE_LIVE_PORT(port);
    SCM_CHARPORT_PUT_CHAR(SCM_PORT_IMPL(port), ch);
}

SCM_EXPORT void
scm_port_flush(ScmObj port)
{
    SCM_ENSURE_LIVE_PORT(port);
    SCM_CHARPORT_FLUSH(SCM_PORT_IMPL(port));
}

/*=======================================
  R5RS : 6.6 Input and Output
=======================================*/
/*===========================================================================
  R5RS : 6.6 Input and Output : 6.6.1 Ports
===========================================================================*/
/* call-with-input-file, call-with-output-file, with-input-from-file and
 * with-output-to-file are implemented in lib/sigscheme-init.scm */

SCM_EXPORT ScmObj
scm_p_input_portp(ScmObj port)
{
    DECLARE_FUNCTION("input-port?", procedure_fixed_1);

    ENSURE_PORT(port);

    return MAKE_BOOL(SCM_PORT_FLAG(port) & SCM_PORTFLAG_INPUT);
}

SCM_EXPORT ScmObj
scm_p_output_portp(ScmObj port)
{
    DECLARE_FUNCTION("output-port?", procedure_fixed_1);

    ENSURE_PORT(port);

    return MAKE_BOOL(SCM_PORT_FLAG(port) & SCM_PORTFLAG_OUTPUT);
}

SCM_EXPORT ScmObj
scm_p_current_input_port(void)
{
    DECLARE_FUNCTION("current-input-port", procedure_fixed_0);

    return scm_in;
}

SCM_EXPORT ScmObj
scm_p_current_output_port(void)
{
    DECLARE_FUNCTION("current-output-port", procedure_fixed_0);

    return scm_out;
}

SCM_EXPORT ScmObj
scm_p_current_error_port(void)
{
    DECLARE_FUNCTION("%%current-error-port", procedure_fixed_0);

    return scm_err;
}

SCM_EXPORT ScmObj
scm_p_set_current_input_portx(ScmObj newport)
{
    DECLARE_FUNCTION("%%set-current-input-port!", procedure_fixed_1);

    SCM_ENSURE_LIVE_PORT(newport);
    if (!(SCM_PORT_FLAG(newport) & SCM_PORTFLAG_INPUT))
        ERR_OBJ("input port required but got", newport);

    scm_in = newport;

    return SCM_TRUE;
}

SCM_EXPORT ScmObj
scm_p_set_current_output_portx(ScmObj newport)
{
    DECLARE_FUNCTION("%%set-current-output-port!", procedure_fixed_1);

    SCM_ENSURE_LIVE_PORT(newport);
    if (!(SCM_PORT_FLAG(newport) & SCM_PORTFLAG_OUTPUT))
        ERR_OBJ("output port required but got", newport);

    scm_out = newport;

    return SCM_TRUE;
}

SCM_EXPORT ScmObj
scm_p_set_current_error_portx(ScmObj newport)
{
    DECLARE_FUNCTION("%%set-current-error-port!", procedure_fixed_1);

    SCM_ENSURE_LIVE_PORT(newport);
    if (!(SCM_PORT_FLAG(newport) & SCM_PORTFLAG_OUTPUT))
        ERR_OBJ("output port required but got", newport);

    scm_err = newport;

    return SCM_TRUE;
}

SCM_EXPORT ScmObj
scm_p_open_input_file(ScmObj filepath)
{
    ScmBytePort *bport;
    ScmCharPort *cport;
    DECLARE_FUNCTION("open-input-file", procedure_fixed_1);

    ENSURE_STRING(filepath);

    bport = ScmFilePort_open_input_file(SCM_STRING_STR(filepath));
    if (!bport)
        ERR_OBJ(ERRMSG_CANNOT_OPEN_FILE, filepath);
    cport = scm_make_char_port(bport);

    return MAKE_PORT(cport, SCM_PORTFLAG_INPUT);
}

SCM_EXPORT ScmObj
scm_p_open_output_file(ScmObj filepath)
{
    ScmBytePort *bport;
    ScmCharPort *cport;
    DECLARE_FUNCTION("open-output-file", procedure_fixed_1);

    ENSURE_STRING(filepath);

    bport = ScmFilePort_open_output_file(SCM_STRING_STR(filepath));
    if (!bport)
        ERR_OBJ(ERRMSG_CANNOT_OPEN_FILE, filepath);
    cport = scm_make_char_port(bport);

    return MAKE_PORT(cport, SCM_PORTFLAG_OUTPUT);
}

SCM_EXPORT ScmObj
scm_p_close_input_port(ScmObj port)
{
    scm_int_t flag;
    DECLARE_FUNCTION("close-input-port", procedure_fixed_1);

    ENSURE_PORT(port);

    flag = SCM_PORT_FLAG(port) & ~SCM_PORTFLAG_LIVE_INPUT;
    SCM_PORT_SET_FLAG(port, flag);
    if (!(flag & SCM_PORTFLAG_ALIVENESS_MASK) && SCM_PORT_IMPL(port))
        scm_port_close(port);

    return SCM_UNDEF;
}

SCM_EXPORT ScmObj
scm_p_close_output_port(ScmObj port)
{
    scm_int_t flag;
    DECLARE_FUNCTION("close-output-port", procedure_fixed_1);

    ENSURE_PORT(port);

    flag = SCM_PORT_FLAG(port) & ~SCM_PORTFLAG_LIVE_OUTPUT;
    SCM_PORT_SET_FLAG(port, flag);
    if (!(flag & SCM_PORTFLAG_ALIVENESS_MASK) && SCM_PORT_IMPL(port))
        scm_port_close(port);

    return SCM_UNDEF;
}

/*===========================================================================
  R5RS : 6.6 Input and Output : 6.6.2 Input
===========================================================================*/
/* scm_p_read() is separated into read.c */

#if SCM_USE_CHAR
SCM_EXPORT ScmObj
scm_p_read_char(ScmObj args)
{
    ScmObj port;
    scm_ichar_t ch;
    DECLARE_FUNCTION("read-char", procedure_variadic_0);

    port = scm_prepare_port(args, scm_in);

    ch = scm_port_get_char(port);
    if (ch == SCM_ICHAR_EOF)
        return SCM_EOF;

    return MAKE_CHAR(ch);
}

SCM_EXPORT ScmObj
scm_p_peek_char(ScmObj args)
{
    ScmObj port;
    scm_ichar_t ch;
    DECLARE_FUNCTION("peek-char", procedure_variadic_0);

    port = scm_prepare_port(args, scm_in);

    ch = scm_port_peek_char(port);
    if (ch == SCM_ICHAR_EOF)
        return SCM_EOF;

    return MAKE_CHAR(ch);
}
#endif /* SCM_USE_CHAR */

SCM_EXPORT ScmObj
scm_p_eof_objectp(ScmObj obj)
{
    DECLARE_FUNCTION("eof-object?", procedure_fixed_1);

    return MAKE_BOOL(EOFP(obj));
}

#if SCM_USE_CHAR
SCM_EXPORT ScmObj
scm_p_char_readyp(ScmObj args)
{
    ScmObj port;
    scm_bool ret;
    DECLARE_FUNCTION("char-ready?", procedure_variadic_0);

    port = scm_prepare_port(args, scm_in);
    ret = scm_port_char_readyp(port);

    return MAKE_BOOL(ret);
}
#endif /* SCM_USE_CHAR */

/*===========================================================================
  R5RS : 6.6 Input and Output : 6.6.3 Output
===========================================================================*/
/* scm_p_write() and scm_p_display() are separated into write.c */

SCM_EXPORT ScmObj
scm_p_newline(ScmObj args)
{
    ScmObj port;
    DECLARE_FUNCTION("newline", procedure_variadic_0);

    port = scm_prepare_port(args, scm_out);
    scm_port_newline(port);
    return SCM_UNDEF;
}

#if SCM_USE_CHAR
SCM_EXPORT ScmObj
scm_p_write_char(ScmObj obj, ScmObj args)
{
    ScmObj port;
    DECLARE_FUNCTION("write-char", procedure_variadic_1);

    ENSURE_CHAR(obj);

    port = scm_prepare_port(args, scm_out);
    scm_port_put_char(port, SCM_CHAR_VALUE(obj));
    return SCM_UNDEF;
}
#endif /* SCM_USE_CHAR */
