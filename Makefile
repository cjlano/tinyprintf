
CPPFLAGS+=-I.
CFLAGS+=-Wall -W -Wextra -O3 -g
# RUNNER:=valgrind

all: printf_test sprintf_test

tests: printf_test sprintf_test
	$(RUNNER) ./printf_test
	$(RUNNER) ./sprintf_test

printf_test: printf_test.o tfp_printf.o tfp_format.o
sprintf_test: sprintf_test.o tfp_sprintf.o tfp_format.o

printf_test sprintf_test:
	$(CC) -o $@ $^

clean:
	$(RM) printf_test sprintf_test *~ *.o
