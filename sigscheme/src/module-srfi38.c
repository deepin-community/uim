/*===========================================================================
 *  Filename : module-srfi38.c
 *  About    : SRFI-38 External Representation for Data With Shared Structure
 *
 *  Copyright (C) 2005-2006 Jun Inoue <jun.lambda AT gmail.com>
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

/* Only write/ss is provided currently. */

#include <config.h>

#include "sigscheme.h"
#include "sigschemeinternal.h"

/*=======================================
  File Local Macro Definitions
=======================================*/

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  Variable Definitions
=======================================*/
#include "functable-srfi38.c"

/*=======================================
  File Local Function Declarations
=======================================*/

/*=======================================
  Function Definitions
=======================================*/
SCM_EXPORT void
scm_initialize_srfi38(void)
{
    scm_register_funcs(scm_functable_srfi38);

    /* SRFI-38 allows providing (read/ss) and (write/ss) */
    scm_define_alias("write/ss", "write-with-shared-structure");

    scm_write_ss_func = scm_write_ss;
}

/*===========================================================================
  SRFI38 : External Representation for Data With Shared Structure
===========================================================================*/
SCM_EXPORT ScmObj
scm_p_srfi38_write_with_shared_structure(ScmObj obj, ScmObj args)
{
    ScmObj port;
    DECLARE_FUNCTION("write-with-shared-structure", procedure_variadic_1);

    /* Omit optarg as same as the reference implementation. */
    if (CONSP(args) && CONSP(CDR(args)))
        args = LIST_1(CAR(args));
    port = scm_prepare_port(args, scm_out);

    scm_write_ss(port, obj);
    return SCM_UNDEF;
}
