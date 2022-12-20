/*===========================================================================
 *  Filename : module-srfi2.c
 *  About    : SRFI-2 AND-LET*: an AND with local bindings, a guarded LET*
 *             special form
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

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  Variable Definitions
=======================================*/
#include "functable-srfi2.c"

/*=======================================
  File Local Function Declarations
=======================================*/

/*=======================================
  Function Definitions
=======================================*/
SCM_EXPORT void
scm_initialize_srfi2(void)
{
    scm_register_funcs(scm_functable_srfi2);
}

SCM_EXPORT ScmObj
scm_s_srfi2_and_letstar(ScmObj claws, ScmObj body, ScmEvalState *eval_state)
{
    ScmObj env, claw, var, val, exp;
    DECLARE_FUNCTION("and-let*", syntax_variadic_tailrec_1);

    env = eval_state->env;

    /*=======================================================================
      (and-let* <claws> <body>)

      <claws> ::= '() | (cons <claw> <claws>)
      <claw>  ::=  (<variable> <expression>) | (<expression>)
                   | <bound-variable>
    =======================================================================*/
    val = SCM_TRUE;
    FOR_EACH (claw, claws) {
        if (CONSP(claw)) {
            if (NULLP(CDR(claw))) {
                /* (<expression>) */
                exp = CAR(claw);
                val = EVAL(exp, env);
                CHECK_VALID_EVALED_VALUE(val);
            } else if (IDENTIFIERP(CAR(claw))) {
                /* (<variable> <expression>) */
                if (!LIST_2_P(claw))
                    goto err;
                var = CAR(claw);
                exp = CADR(claw);
                val = EVAL(exp, env);
                CHECK_VALID_EVALED_VALUE(val);
                env = scm_extend_environment(LIST_1(var), LIST_1(val), env);
            } else {
                goto err;
            }
        } else if (IDENTIFIERP(claw)) {
            /* <bound-variable> */
            val = EVAL(claw, env);
            CHECK_VALID_EVALED_VALUE(val);
        } else {
            goto err;
        }
        if (FALSEP(val)) {
            eval_state->ret_type = SCM_VALTYPE_AS_IS;
            return SCM_FALSE;
        }
    }
    if (!NULLP(claws))
        goto err;

    eval_state->env = env;

    /* SRFI-2 Formal (Denotational) Semantics:
     *   eval[ (AND-LET* (CLAW) ), env] = eval_claw[ CLAW, env ]
     *   eval[ (AND-LET* () ), env] = #t                           */
    if (NULLP(body)) {
        eval_state->ret_type = SCM_VALTYPE_AS_IS;
        return val;
    } else {
        return scm_s_body(body, eval_state);
    }

 err:
    ERR_OBJ("invalid claws form", claws);
    /* NOTREACHED */
    return SCM_FALSE;
}
