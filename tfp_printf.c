/*
File: tfp_sprintf.c

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

*/

#include "tfp_format.h"
#include "tfp_printf.h"

static putcf stdout_putf;
static void *stdout_putp;

void tfp_init_printf(void *putp, void (*putf) (void *, char))
{
    stdout_putf = putf;
    stdout_putp = putp;
}

void tfp_vprintf(const char *fmt, va_list ap)
{
    tfp_format(stdout_putp, stdout_putf, fmt, ap);
}

void tfp_printf(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    tfp_format(stdout_putp, stdout_putf, fmt, va);
    va_end(va);
}
