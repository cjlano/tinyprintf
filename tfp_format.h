/*
File: printf.h

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

This library is realy just two files: 'tfp_format.h' and 'tfp_format.c'.

They provide a simple and small (+200 loc) printf functionality to
be used in embedded systems.

I've found them so usefull in debugging that I do not bother with a
debugger at all.

They are distributed in source form, so to use them, just compile them
into your project.

Two printf variants are provided: sprintf in tfp_sprintf.{c,h} and
printf in tfp_printf.{c,h}.

The formats supported by this implementation are: 'd' 'u' 'c' 's' 'x'
'X' 'o', 'p'.

Zero padding, field width and left/right alignment are also supported.

If the library is compiled with 'PRINTF_LONG_SUPPORT' defined then the
long specifier is also supported. Likewise for
PRINTF_LONG_LONG_SUPPORT wth long long int type & associated
specifier. Note that this will pull in some long math routines (pun
intended!)  and thus make your executable noticably longer.

The memory foot print of course depends on the target cpu, compiler and
compiler options, but a rough guestimate (based on a H8S target) is about
1.4 kB for code and some twenty 'int's and 'char's, say 60 bytes of stack space.
Not too bad. Your milage may vary. By hacking the source code you can
get rid of some hunred bytes, I'm sure, but personally I feel the balance of
functionality and flexibility versus  code size is close to optimal for
many embedded systems.

To use tfp_format(), you need to supply your own character output
function, something like :

void putc ( void* p, char c)
{
    while (!SERIAL_PORT_EMPTY) ;
    SERIAL_PORT_TX_REGISTER = c;
}

The argument 'p' above is coming from tfp_format's putp argument, can
be anything to your liking. Argument 'c' corresponds to each character
to be "printed".

The code is re-entrant, so it is safe to call it from interupts too,
although this may result in mixed output.  If you rely on re-entrancy,
take care that your 'putc' function is re-entrant.

See tfp_sprintf.{c,h} and tfp_printf.{c,h} for examples.

For further details see source code.

regs Kusti, 23.10.2004
*/

#ifndef __TFP_FORMAT_H__
#define __TFP_FORMAT_H__

#include <stdarg.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef void (*putcf) (void *, char);

void tfp_format(void *putp, void (*putf) (void *, char),
                const char *fmt, va_list va);

#ifdef  __cplusplus
}
#endif

#endif
