/*===========================================================================
 *  Filename : number-io.c
 *  About    : Numerical input/output procedures of R5RS numbers
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

#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#if SCM_STRICT_ARGCHECK
#include <string.h>
#endif

#include "sigscheme.h"
#include "sigschemeinternal.h"

/*=======================================
  File Local Macro Definitions
=======================================*/
#define VALID_RADIXP(r) ((r) == 2 || (r) == 8 || (r) == 10 || (r) == 16)

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  Variable Definitions
=======================================*/

/*=======================================
  File Local Function Declarations
=======================================*/
#if SCM_USE_STRING
static int prepare_radix(const char *funcname, ScmObj args);
#endif

/*=======================================
  Function Definitions
=======================================*/
/*===========================================================================
  R5RS : 6.2 Numbers : 6.2.6 Numerical input and output
===========================================================================*/
#if SCM_USE_STRING
static int
prepare_radix(const char *funcname, ScmObj args)
{
    ScmObj radix;
    int r;
    DECLARE_INTERNAL_FUNCTION("(internal)");

    ASSERT_PROPER_ARG_LIST(args);

    /* dirty hack to replace internal function name */
    SCM_MANGLE(name) = funcname;

    if (NULLP(args)) {
        r = 10;
    } else {
        radix = POP(args);
        ASSERT_NO_MORE_ARG(args);
        ENSURE_INT(radix);
        r = SCM_INT_VALUE(radix);
        if (!VALID_RADIXP(r))
            ERR_OBJ("invalid radix", radix);
    }

    return r;
}

SCM_EXPORT char *
scm_int2string(ScmValueFormat vfmt, uintmax_t n, int radix)
{
    char buf[sizeof("-") + sizeof(uintmax_t) * CHAR_BIT];
    char *p, *end, *str;
    uintmax_t un;  /* must be unsigned to be capable of -INT_MIN */
    int digit, sign_len, pad_len, len;
    scm_bool neg;
    DECLARE_INTERNAL_FUNCTION("scm_int2string");

    SCM_ASSERT(VALID_RADIXP(radix));
    neg = (vfmt.signedp && ((intmax_t)n < 0));
    un = (neg) ? (uintmax_t)-(intmax_t)n : n;

    end = p = &buf[sizeof(buf) - 1];
    *end = '\0';

    do {
        digit = un % radix;
        *--p = (digit <= 9) ? '0' + digit : 'a' + digit - 10;
    } while (un /= radix);
    if (neg && vfmt.pad != '0')
        *--p = '-';

    sign_len = (neg && vfmt.pad == '0') ? 1 : 0;
    len = end - p;
    pad_len = (sign_len + len < vfmt.width) ? vfmt.width - sign_len - len : 0;

    str = scm_malloc(sign_len + pad_len + len + sizeof(""));
    strcpy(&str[sign_len + pad_len], p);
    while (pad_len)
        str[sign_len + --pad_len] = vfmt.pad;

    if (sign_len)
        *str = '-';

    return str;
}

SCM_EXPORT ScmObj
scm_p_number2string(ScmObj num, ScmObj args)
{
    char *str;
    intmax_t n;
    int r;
    ScmValueFormat vfmt;
    DECLARE_FUNCTION("number->string", procedure_variadic_1);

    ENSURE_INT(num);

    n = (intmax_t)SCM_INT_VALUE(num);
    r = prepare_radix(SCM_MANGLE(name), args);
    SCM_VALUE_FORMAT_INIT(vfmt);
    str = scm_int2string(vfmt, (uintmax_t)n, r);

    return MAKE_STRING(str, SCM_STRLEN_UNKNOWN);
}
#endif /* SCM_USE_STRING */

SCM_EXPORT scm_int_t
scm_string2number(const char *str, int radix, scm_bool *err)
{
    scm_int_t n;
    char *end;
    scm_bool empty_strp;
    DECLARE_INTERNAL_FUNCTION("string->number");

    SCM_ASSERT(str);
    SCM_ASSERT(VALID_RADIXP(radix));
    SCM_ASSERT(err);

    /* R5RS:
     *
     * - If string is not a syntactically valid notation for a number, then
     *   `string->number' returns #f.
     *
     * - `String->number' is permitted to return #f whenever string contains an
     *   explicit radix prefix.
     *
     * - If all numbers supported by an implementation are real, then
     *   `string->number' is permitted to return #f whenever string uses the
     *   polar or rectangular notations for complex numbers.
     *
     * - If all numbers are integers, then `string->number' may return #f
     *   whenever the fractional notation is used.
     *
     * - If all numbers are exact, then `string->number' may return #f whenever
     *   an exponent marker or explicit exactness prefix is used, or if a #
     *   appears in place of a digit.
     *
     * - If all inexact numbers are integers, then `string->number' may return
     *   #f whenever a decimal point is used.
     */

#if SCM_STRICT_ARGCHECK
    /* Reject "0xa", " 1" etc. */
    if ((*err = str[strspn(str, "0123456789abcdefABCDEF-+")]))
        return 0;
#endif /* SCM_STRICT_ARGCHECK */

    errno = 0;
#if (SIZEOF_SCM_INT_T <= SIZEOF_LONG)
    n = (scm_int_t)strtol(str, &end, radix);
#elif (HAVE_STRTOLL && SIZEOF_SCM_INT_T <= SIZEOF_LONG_LONG)
    n = (scm_int_t)strtoll(str, &end, radix);
#elif (HAVE_STRTOIMAX && SIZEOF_SCM_INT_T <= SIZEOF_INTMAX_T)
    n = (scm_int_t)strtoimax(str, &end, radix);
#else
#error "This platform is not supported"
#endif

    empty_strp = (end == str);  /* apply the first rule above */
    *err = (empty_strp || *end);

    /*
     * glibc warning: Although the manpage describes the behavior as follows,
     * ERANGE is returned for "". The description "may be set to [EINVAL]" is
     * really 'may'. And the ISO C standard does not define errno for the
     * case. So we should not depend on the assumption that ERANGE is returned
     * only when overflow/underflow is occurred.
     *
     * quoted from glibc 2.3:
     *   RETURN VALUE
     *     Upon successful completion, these functions shall return the
     *     converted value, if any. If no conversion could be performed, 0
     *     shall be returned and errno may be set to [EINVAL].
     */
    if ((errno == ERANGE && !empty_strp) || INT_OUT_OF_RANGEP(n)) {
#if 0
        ERR(ERRMSG_FIXNUM_OVERFLOW ": ~S (radix ~D)", str, radix);
#else
        /* R5RS: If string is not a syntactically valid notation for a number,
         *       then `string->number' returns #f.  */
        *err = scm_true;
        n = 0;
#endif
    }

    return n;
}

#if SCM_USE_STRING
SCM_EXPORT ScmObj
scm_p_string2number(ScmObj str, ScmObj args)
{
    scm_int_t ret;
    int r;
    const char *c_str;
    scm_bool err;
    DECLARE_FUNCTION("string->number", procedure_variadic_1);

    ENSURE_STRING(str);

    c_str = SCM_STRING_STR(str);
    r = prepare_radix(SCM_MANGLE(name), args);

    ret = scm_string2number(c_str, r, &err);
    return (err) ? SCM_FALSE : MAKE_INT(ret);
}
#endif /* SCM_USE_STRING */
