/*===========================================================================
 *  Filename : load.c
 *  About    : Code loading
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sigscheme.h"
#include "sigschemeinternal.h"
#if SCM_USE_MULTIBYTE_CHAR
#include "scmport-config.h"
#include "scmport.h"
#include "scmport-mbchar.h"
#endif

/*=======================================
  File Local Macro Definitions
=======================================*/
/* FIXME: only supports UNIX flavors */
#define ABSOLUTE_PATHP(path) ((path)[0] == '/')
#define PATH_SEPARATOR ':'

#if SCM_USE_SRFI22
/* SRFI-22: The <script prelude> line may not be longer than 64 characters. */
#define SCRIPT_PRELUDE_MAXLEN 64
#define SCRIPT_PRELUDE_DELIM  " \t\n\r"
#endif

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  Variable Definitions
=======================================*/
#include "functable-r5rs-load.c"

SCM_GLOBAL_VARS_BEGIN(static_load);
#define static
static char *l_scm_lib_path, *l_scm_system_load_path;
#undef static
SCM_GLOBAL_VARS_END(static_load);
#define l_scm_lib_path         SCM_GLOBAL_VAR(static_load, l_scm_lib_path)
#define l_scm_system_load_path SCM_GLOBAL_VAR(static_load, l_scm_system_load_path)
SCM_DEFINE_STATIC_VARS(static_load);

/*=======================================
  File Local Function Declarations
=======================================*/
static void *scm_load_internal(const char *filename);
static char *find_path(const char *filename);
static scm_bool file_existsp(const char *filepath);
#if SCM_USE_SRFI22
static void interpret_script_prelude(ScmObj port);
static char **parse_script_prelude(ScmObj port);
#endif

/*=======================================
  Function Definitions
=======================================*/
SCM_EXPORT void
scm_init_load(void)
{
    SCM_GLOBAL_VARS_INIT(static_load);

    scm_register_funcs(scm_functable_r5rs_load);
}

SCM_EXPORT void
scm_fin_load(void)
{
    free(l_scm_lib_path);
    free(l_scm_system_load_path);

    l_scm_system_load_path = NULL;

    SCM_GLOBAL_VARS_FIN(static_load);
}

/* Don't provide any Scheme procedure to call this function, to avoid security
 * problems. User modification of the value or relative path capability may
 * cause arbitrary C code injection by plugin spoofing when future SigScheme
 * has been added C plugin feature. It could be a serious vulnerability if the
 * libsscm client is a setugid'ed command. -- YamaKen 2006-03-25 */
SCM_EXPORT void
scm_set_lib_path(const char *path)
{
    const char *begin, *end;
    DECLARE_INTERNAL_FUNCTION("scm_set_lib_path");

    begin = path;
    while (begin[0] != '\0') {
        while (begin[0] == PATH_SEPARATOR)
            begin++;

        end = begin;
        while (end[0] != '\0' && end[0] != PATH_SEPARATOR)
            end++;

        if (!ABSOLUTE_PATHP(begin))
            ERR("library path must be absolute but got: ~S", path);
        begin = end;
    }

    free(l_scm_lib_path);
    l_scm_lib_path = (path) ? scm_strdup(path) : NULL;
}

/* SigScheme specific procedure (SIOD compatible) */
SCM_EXPORT ScmObj
scm_p_load_path(void)
{
    DECLARE_FUNCTION("load-path", procedure_fixed_0);

    return CONST_STRING(l_scm_lib_path);
}

SCM_EXPORT void
scm_load_system_file(const char *file)
{
    ScmObj path;
    DECLARE_INTERNAL_FUNCTION("scm_load_system_file");

    path = scm_p_string_append(LIST_3(scm_p_system_load_path(),
                                      CONST_STRING("/"),
                                      CONST_STRING(file)));
    scm_p_load(path);
}

SCM_EXPORT void
scm_set_system_load_path(const char *path)
{
    DECLARE_INTERNAL_FUNCTION("scm_set_system_load_path");

    if (!ABSOLUTE_PATHP(path))
        ERR("library path must be absolute but got: ~S", path);

    free(l_scm_system_load_path);
    l_scm_system_load_path = (path) ? scm_strdup(path) : NULL;
}

SCM_EXPORT ScmObj
scm_p_system_load_path(void)
{
    const char *path;
    DECLARE_FUNCTION("%%system-load-path", procedure_fixed_0);

    path = (l_scm_system_load_path) ? l_scm_system_load_path : SCMLIBDIR;
    return CONST_STRING(path);
}

/*===========================================================================
  R5RS : 6.6 Input and Output : 6.6.4 System Interface
===========================================================================*/
SCM_EXPORT void
scm_load(const char *filename)
{
    scm_call_with_gc_ready_stack((ScmGCGateFunc)scm_load_internal,
                                 (void *)filename);
}

/* FIXME: scm_current_char_codec on an exception */
static void *
scm_load_internal(const char *filename)
{
    ScmObj path, port, sexp;
    char *c_path;
#if SCM_USE_MULTIBYTE_CHAR
    ScmCharCodec *saved_codec;
#endif
    DECLARE_INTERNAL_FUNCTION("load");

    CDBG((SCM_DBG_FILE, "loading ~S", filename));

    c_path = find_path(filename);
    if (!c_path)
        ERR("file \"~S\" not found", filename);

    path = MAKE_IMMUTABLE_STRING(c_path, STRLEN_UNKNOWN);
    port = scm_p_open_input_file(path);

#if SCM_USE_MULTIBYTE_CHAR
    saved_codec = scm_current_char_codec;
#endif
#if SCM_USE_SRFI22
    if (scm_port_peek_char(port) == '#')
        interpret_script_prelude(port);
#endif

    /* read & eval cycle */
    while (sexp = scm_read(port), !EOFP(sexp))
        EVAL(sexp, SCM_INTERACTION_ENV);

    scm_p_close_input_port(port);
#if SCM_USE_MULTIBYTE_CHAR
    scm_current_char_codec = saved_codec;
#endif

    CDBG((SCM_DBG_FILE, "done."));
    return NULL;
}

static char *
find_path(const char *filename)
{
    char *path;
    const char *begin, *end;
    size_t lib_path_len, filename_len, path_len;

    SCM_ASSERT(filename);

    /* try absolute path */
    if (file_existsp(filename))
        return scm_strdup(filename);

    /* try under l_scm_lib_path */
    /* l_scm_lib_path is separated with PATH_SEPARATOR */
    if (l_scm_lib_path) {
        begin = l_scm_lib_path;
        while (begin[0] != '\0') {
            while (begin[0] == PATH_SEPARATOR)
                begin++;

            end = begin;
            while (end[0] != '\0' && end[0] != PATH_SEPARATOR)
                end++;

            if (end > begin)
                lib_path_len = end - begin;
            else
                lib_path_len = 0;
            filename_len = strlen(filename);
            path_len = lib_path_len + sizeof((char)'/') + filename_len + sizeof("");

            path = scm_malloc(path_len);
            strncpy(path, begin, lib_path_len);
            path[lib_path_len] = '\0';
            strcat(path, "/");
            strcat(path, filename);
            if (file_existsp(path))
                return path;
            free(path);
            begin = end;
        }
    }

    return NULL;
}

static scm_bool
file_existsp(const char *filepath)
{
    FILE *f;

    SCM_ASSERT(filepath);

    if (!ABSOLUTE_PATHP(filepath))
        return scm_false;

    f = fopen(filepath, "r");
    if (f) {
        fclose(f);
        return scm_true;
    } else {
        return scm_false;
    }
}

SCM_EXPORT ScmObj
scm_p_load(ScmObj filename)
{
    DECLARE_FUNCTION("load", procedure_fixed_1);

    ENSURE_STRING(filename);

    scm_load_internal(SCM_STRING_STR(filename));

    return SCM_UNDEF;
}

#if SCM_USE_SRFI22
static void
interpret_script_prelude(ScmObj port)
{
    char **argv;

    argv = parse_script_prelude(port);
    scm_interpret_argv(argv);
#if SCM_USE_MULTIBYTE_CHAR
    if (SCM_CHARPORT_DYNAMIC_CAST(ScmMultiByteCharPort, SCM_PORT_IMPL(port))) {
        ScmMultiByteCharPort_set_codec(SCM_PORT_IMPL(port),
                                       scm_current_char_codec);
    }
#endif
    scm_free_argv(argv);
}

static char **
parse_script_prelude(ScmObj port)
{
    scm_ichar_t c;
    int argc, len, line_len;
    char **argv, *arg, *p;
    char line[SCRIPT_PRELUDE_MAXLEN];

    for (p = line; p < &line[SCRIPT_PRELUDE_MAXLEN]; p++) {
        c = scm_port_get_char(port);
        if (!ICHAR_ASCIIP(c))
            PLAIN_ERR("non-ASCII char appeared in UNIX script prelude");
        if (c == SCM_NEWLINE_STR[0]) {
            *p = '\0';
            break;
        }
        *p = c;
    }
    if (p == &line[SCRIPT_PRELUDE_MAXLEN])
        PLAIN_ERR("too long UNIX script prelude (max 64)");
    line_len = p - line;

    if (line[0] != '#' || line[1] != '!') {
        PLAIN_ERR("invalid UNIX script prelude");
    }
#if 1
    /* strict check */
    if (line[2] != ' ') {
        PLAIN_ERR("invalid UNIX script prelude: "
                  "SRFI-22 requires a space after hash-bang sequence");
    }
#endif

    argv = scm_malloc(sizeof(char *));
    argv[0] = NULL;
    argc = 0;
    for (p = &line[3]; p < &line[line_len]; p += len + sizeof((char)'\0')) {
        p += strspn(p, SCRIPT_PRELUDE_DELIM);
        len = strcspn(p, SCRIPT_PRELUDE_DELIM);
        if (!len)
            break;
        p[len] = '\0';
        arg = scm_strdup(p);
        argv[argc] = arg;
        argv = scm_realloc(argv, sizeof(char *) * (++argc + 1));
        argv[argc] = NULL;
    }

    return argv;
}
#endif /* SCM_USE_SRFI22 */
