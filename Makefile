
CPPFLAGS+=-I.
CFLAGS+=-Wall -W -Wextra -O3 -g
# RUNNER:=valgrind

.PHONY: all test tests clean

all: tests

test tests: test/printf
	$(RUNNER) $<

test/printf: test/printf.o tinyprintf.o
	$(LINK.c) -o $@ $^

clean:
	$(RM) *.o test/*.o *~ test/*~ test/printf
