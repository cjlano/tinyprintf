/*
File: tfp_sprintf.h

Copyright (C) 2004  Kustaa Nyholm

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

This file implements the sprintf functions according to C99 standards
as far as their signature and return value are concerned: supported
format is a subset of C99's (see tfp_format.h for details).

If the macro TFP_PRINTF_IS_STDIO is defined, The v?(s|sn)printf
functions are actually macros that translate to 'tfp_Xprintf'
functions. Note that these are not function like macros, so if you
have variables or struct members with these names, things will explode
in your face.  Without variadic macros this is the best we can do to
wrap these fucnction. If it is a problem just give up the macros and
use the functions directly or rename them.

The code is re-entrant, so it is safe to call it from interupts too,
although this may result in mixed output.

For further details see source code.

regs Kusti, 23.10.2004
*/

#ifndef __TFP_SPRINTF_H__
#define __TFP_SPRINTF_H__

#include <sys/types.h>  /* size_t */
#include <stdarg.h>

#ifdef __GNUC__
# define PRINTF_FMT(fmt_idx,arg1_idx) \
    __attribute__((format (printf, fmt_idx, arg1_idx)))
#else
# define PRINTF_FMT(fmt_idx,arg1_idx)
#endif

#ifdef  __cplusplus
extern "C" {
#endif

int tfp_vsprintf(char *str, const char *fmt, va_list ap);
int tfp_vsnprintf(char *str, size_t size, const char *fmt, va_list ap);
int tfp_sprintf(char *str, const char *fmt, ...) PRINTF_FMT(2,3);
int tfp_snprintf(char *str, size_t size, const char *fmt, ...) PRINTF_FMT(3,4);

#ifdef  __cplusplus
}
#endif

#ifdef TFP_PRINTF_IS_STDIO
# define vsprintf  tfp_vsprintf
# define vsnprintf tfp_vsnprintf
# define sprintf   tfp_sprintf
# define snprintf  tfp_snprintf
#endif

#endif
