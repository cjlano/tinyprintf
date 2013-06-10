
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "tfp_sprintf.h"

/* Use malloc so that valgrind can catch array overflows */
#define TPRINTF(expr...)                                                \
  ({ char *s1, *s2; size_t sz1, sz2;                                    \
    /* Test format ok */                                                \
    s1 = malloc(1024); s2 = malloc(1024);                               \
    sz1 = snprintf(s1, 1024, expr); sz2 = tfp_snprintf(s2, 256, expr);  \
    printf("libc_snprintf(%s) -> %d: ", #expr, (int)sz1); puts(s1);     \
    printf(" tfp_snprintf(%s) -> %d: ", #expr, (int)sz2); puts(s2);     \
    assert(sz1 == sz2);                                                 \
    assert(0 == strcmp(s1, s2));                                        \
    /* Test no array verflow */                                         \
    free(s1); free(s2); s1 = malloc(1); s2 = malloc(1);                 \
    assert(snprintf(s1, 1, expr) == tfp_snprintf(s2, 1, expr));         \
    assert(strlen(s1) == 0); assert(strlen(s2) == 0);                   \
    assert(0 == strcmp(s1, s2));                                        \
    /* Test correct truncation */                                       \
    free(s1); free(s2); s1 = malloc(16); s2 = malloc(16);               \
    assert(snprintf(s1, 16, expr) == tfp_snprintf(s2, 16, expr));       \
    assert(strlen(s1) < 16); assert(strlen(s2) < 16);                   \
    assert(0 == strcmp(s1, s2));                                        \
    free(s1); free(s2);                                                 \
  })


int main()
{
  printf("Fun with %%!\n");

  TPRINTF("d1=%016llx d2=%016lx d3=%02x d4=%02X 42=%03d",
          (long long unsigned)0xd1, (long unsigned)0xd2, 0xd3, 0xd4, 42);
  TPRINTF("d1=%04x d2=%06x d3=%08x %%100", 0xd1, 0xd2, 0xd3);
  TPRINTF("|%-14s| |%-16s| d2=%2x |%-30s|", "str14", "str16", 0xd2,
          "12345678901234567890123456789012345");
  TPRINTF("|%4s|", "string4");
  TPRINTF("|%-4s|", "string4");
  TPRINTF("42=%3d d1=%4.4x |%4s| d2=%8.8x", 42, 0xd1, "string4", 0xd2);
  TPRINTF("42=%3d d1=%4.4x |%-4s| d2=%8.8x", 42, 0xd1, "string4", 0xd2);
  TPRINTF("84=%d 21=%ds |%s| |%sOK| d1=%x d2=%#x",
          84, 21, "hello", "fine", 0xd1, 0xd2);

  TPRINTF("%lld", -(1ULL << 63));
  TPRINTF("%llu", (1ULL << 64) - 1);
  TPRINTF("%llx", -(1ULL << 63));
  TPRINTF("%llx", (1ULL << 64) - 1);

  TPRINTF("d1=%4.4x", 0xd1);

  TPRINTF("Hello |%15s|.", "12345678901234");

  {
    int in_stack;
    TPRINTF("Adddress of main: %p", main);
    TPRINTF("Adddress of stack variable: %p", &in_stack);
  }

  return 0;
}
