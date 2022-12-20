/*===========================================================================
 *  Filename : dllentry.c
 *  About    : Entry function of dynamic-link library
 *
 *  Copyright (C) 2006 YAMAMOTO Kengo <yamaken AT bp.iij4u.or.jp>
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

/*** EXPERIMENTAL AND NOT TESTED ***/

#if (defined(__SYMBIAN32__) && !defined(EKA2))
/* keep all SigScheme API symbols exported against combined-source mode */
#define SCM_EXPORT_API 1
#include "sigscheme-combined.c"
#endif

#ifdef __SYMBIAN32__
#include <e32std.h>
#endif

/*=======================================
  File Local Macro Definitions
=======================================*/

/*=======================================
  File Local Type Definitions
=======================================*/

/*=======================================
  Variable Definitions
=======================================*/

/*=======================================
  File Local Function Declarations
=======================================*/

/*=======================================
  Function Definitions
=======================================*/
#if defined(__SYMBIAN32__)
EXPORT_C TInt
E32Dll(TDllReason reason)
{
    return KErrNone;
}
#elif (defined(_WIN32) || defined(_WIN64))
#error "This platform is not supported yet"
#endif
