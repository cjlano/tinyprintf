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

This file implements the printf functions. They do not adhere to the
C99 standards, in that their return type is void instead of int. This
makes their stack requirements slighly smaller.

Before you can call printf you need to initialize it to use your
character output function with something like:

tfp_init_printf(NULL,putc);

Notice the 'NULL' in 'init_printf' and the parameter 'void* p' in 'putc',
the NULL (or any pointer) you pass into the 'init_printf' will eventually be
passed to your 'putc' routine. This allows you to pass some storage space (or
anything realy) to the character output function, if necessary.

The code is re-entrant, except for the 'tfp_init_printf' function, so it
is safe to call it from interupts too, although this may result in mixed output.
If you rely on re-entrancy, take care that your 'putc' function is re-entrant!

If the macro TFP_PRINTF_IS_STDIO is defined, The printf and sprintf
functions are actually macros that translate to 'tfp_printf' and
'tfp_sprintf'. This makes it possible to use them along with 'stdio.h'
printf's in a single source file.  Note that these are not function
like macros, so if you have variables or struct members with these
names, things will explode in your face.  Without variadic macros this
is the best we can do to wrap these fucnction. If it is a problem just
give up the macros and use the functions directly or rename them.

regs Kusti, 23.10.2004
*/

#ifndef __TFP_PRINTF_H__
#define __TFP_PRINTF_H__

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

void tfp_init_printf(void *putp, void (*putf) (void *, char));

void tfp_printf(const char *format, ...) PRINTF_FMT(1,2);
void tfp_vprintf(const char *format, va_list ap);

#ifdef  __cplusplus
}
#endif

#ifdef TFP_PRINTF_IS_STDIO
# define printf  tfp_printf
# define vprintf tfp_vprintf
#endif

#endif
