/*===========================================================================
 *  Filename : module.c
 *  About    : Code module handlings
 *
 *  Copyright (C) 2005      Kazuki Ohta <mover AT hct.zaq.ne.jp>
 *  Copyright (C) 2005      Jun Inoue <jun.lambda AT gmail.com>
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
#include <string.h>

#include "sigscheme.h"
#include "sigschemeinternal.h"

/*=======================================
  File Local Macro Definitions
=======================================*/

/*=======================================
  File Local Type Definitions
=======================================*/
/* Since Solaris is having struct module_info, 'scm_' prefix is mandatory. */
struct scm_module_info {
    const char *name;
    void (*initializer)(void);
    void (*finalizer)(void);
};

/*=======================================
  Variable Definitions
=======================================*/
SCM_GLOBAL_VARS_BEGIN(static_module);
#define static
static ScmObj l_features;
static ScmObj l_provided_modules;
#undef static
SCM_GLOBAL_VARS_END(static_module);
#define l_features         SCM_GLOBAL_VAR(static_module, l_features)
#define l_provided_modules SCM_GLOBAL_VAR(static_module, l_provided_modules)
SCM_DEFINE_STATIC_VARS(static_module);

static const struct scm_module_info module_info_table[] = {
#if SCM_USE_SSCM_EXTENSIONS
    {"sscm-ext", scm_initialize_sscm_extensions, NULL},
#endif
#if SCM_USE_SRFI1
    {"srfi-1", scm_initialize_srfi1, NULL},
#endif
#if SCM_USE_SRFI2
    {"srfi-2", scm_initialize_srfi2, NULL},
#endif
#if SCM_USE_SRFI6
    {"srfi-6", scm_initialize_srfi6, NULL},
#endif
#if SCM_USE_SRFI8
    {"srfi-8", scm_initialize_srfi8, NULL},
#endif
#if SCM_USE_SRFI9
    {"srfi-9", scm_initialize_srfi9, NULL},
#endif
#if SCM_USE_SRFI23
    {"srfi-23", scm_initialize_srfi23, NULL},
#endif
#if SCM_USE_SRFI28
    {"srfi-28", scm_initialize_srfi28, NULL},
#endif
#if SCM_USE_SRFI34
    {"srfi-34", scm_initialize_srfi34, NULL},
#endif
#if SCM_USE_SRFI38
    {"srfi-38", scm_initialize_srfi38, NULL},
#endif
#if SCM_USE_SRFI43
    {"srfi-43", scm_initialize_srfi43, NULL},
#endif
#if SCM_USE_SRFI48
    {"srfi-48", scm_initialize_srfi48, NULL},
#endif
#if SCM_USE_SRFI55
    {"srfi-55", scm_initialize_srfi55, NULL},
#endif
#if SCM_USE_SRFI60
    {"srfi-60", scm_initialize_srfi60, NULL},
#endif
#if SCM_COMPAT_SIOD
    {"siod", scm_initialize_siod, NULL},
#endif
    {NULL, NULL, NULL}
};

/*=======================================
  File Local Function Declarations
=======================================*/
static const struct scm_module_info *lookup_module_info(const char *feature);
static void *scm_use_internal(const char *feature);
static void *scm_require_module_internal(const char *name);

/*=======================================
  Function Definitions
=======================================*/
static const struct scm_module_info *
lookup_module_info(const char *feature)
{
    const struct scm_module_info *mod;

    for (mod = module_info_table; mod->name; mod++) {
        if (strcmp(feature, mod->name) == 0)
            return mod;
    }

    return NULL;
}

SCM_EXPORT void
scm_init_module(void)
{
    SCM_GLOBAL_VARS_INIT(static_module);

    scm_gc_protect_with_init(&l_features, SCM_NULL);
    scm_gc_protect_with_init(&l_provided_modules, SCM_NULL);
}

SCM_EXPORT void
scm_fin_module(void)
{
    const struct scm_module_info *mod;
    const char *c_mod_name;
    ScmObj mod_name;

    FOR_EACH (mod_name, l_provided_modules) {
        SCM_ASSERT(STRINGP(mod_name));
        c_mod_name = SCM_STRING_STR(mod_name);
        if ((mod = lookup_module_info(c_mod_name)) && mod->finalizer)
            (*mod->finalizer)();
    }

    SCM_GLOBAL_VARS_FIN(static_module);
}

SCM_EXPORT void
scm_provide(ScmObj feature)
{
    SCM_ASSERT(STRINGP(feature));

    l_features = CONS(feature, l_features);
    l_provided_modules = CONS(feature, l_provided_modules);
}

SCM_EXPORT scm_bool
scm_providedp(ScmObj feature)
{
    return TRUEP(scm_p_member(feature, l_features));
}

#if 1  /* 'use' is deprecated and will be removed in SigScheme 0.9 */
SCM_EXPORT scm_bool
scm_use(const char *feature)
{
    return scm_call_with_gc_ready_stack((ScmGCGateFunc)scm_use_internal, (void *)feature) ? scm_true : scm_false;
}

static void *
scm_use_internal(const char *feature)
{
    ScmObj ok;

    SCM_ASSERT(feature);

    ok = scm_s_use(scm_intern(feature), SCM_INTERACTION_ENV);
    return (void *)(uintptr_t)TRUEP(ok);
}

SCM_EXPORT ScmObj
scm_s_use(ScmObj feature, ScmObj env)
{
    const char *c_feature_str;
    DECLARE_FUNCTION("use", syntax_fixed_1);

    ENSURE_SYMBOL(feature);

    c_feature_str = SCM_SYMBOL_NAME(feature);
    return scm_p_require_module(CONST_STRING(c_feature_str));
}
#endif  /* deprecated */

SCM_EXPORT scm_bool
scm_require_module(const char *name)
{
    return scm_call_with_gc_ready_stack((ScmGCGateFunc)scm_require_module_internal, (void *)name) ? scm_true : scm_false;
}

static void *
scm_require_module_internal(const char *name)
{
    ScmObj ok;

    SCM_ASSERT(name);

    ok = scm_p_require_module(CONST_STRING(name));
    return (void *)(uintptr_t)TRUEP(ok);
}

/*
 * TODO:
 * - Make the 'module' concept similar to other Scheme implementations and R6RS
 * - Make the module_info_table dynamically registerable for dynamic loadable
 *   objects (if necessary)
 */
SCM_EXPORT ScmObj
scm_p_require_module(ScmObj name)
{
    const struct scm_module_info *mod;
    const char *c_name;
    DECLARE_FUNCTION("%%require-module", procedure_fixed_1);

    ENSURE_STRING(name);

    c_name = SCM_STRING_STR(name);
    if ((mod = lookup_module_info(c_name))) {
        if (!scm_providedp(name)) {
            (*mod->initializer)();
            scm_provide(name);
        }
        return SCM_TRUE;
    }

    return SCM_FALSE;
}

/*===========================================================================
  Scheme Function Export Related Functions
===========================================================================*/
SCM_EXPORT void
scm_define_alias(const char *newsym, const char *sym)
{
    SCM_SYMBOL_SET_VCELL(scm_intern(newsym),
                         SCM_SYMBOL_VCELL(scm_intern(sym)));
}

SCM_EXPORT void
scm_register_funcs(const struct scm_func_registration_info *table)
{
    const struct scm_func_registration_info *info;

    for (info = &table[0]; info->funcname; info++) {
        scm_register_func(info->funcname, info->c_func, info->typecode);
    }
}

SCM_EXPORT ScmObj
scm_register_func(const char *name, ScmFuncType c_func,
                  enum ScmFuncTypeCode type)
{
    ScmObj sym, func;

    sym  = scm_intern(name);
    func = MAKE_FUNC(type, c_func);

    /* TODO: reject bad TYPE */
    SCM_SYMBOL_SET_VCELL(sym, func);
    return func;
}
