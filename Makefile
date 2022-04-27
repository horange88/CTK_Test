LDFLAGS := -O0 -Wall -Werror -Wextra
LDLIBS := 
CC=gcc
RM=rm -f
INCLUDE= -ILogManager -ITest

SRCS_MAIN=main.c LogManager/LogManager.c
OBJS_MAIN=$(subst .c,.o,$(SRCS_MAIN))

SRCS_TEST=Test/test.c
OBJS_TEST=$(subst .cpp,.o,$(SRCS_GAME))



main: $(OBJS_MAIN)
	$(CC) $(LDFLAGS) -o main $(OBJS_MAIN) $(LDLIBS) $(INCLUDE)

main.o: main.c
	$(CC) $(LDFLAGS) -c -o main.o main.c $(LDLIBS) $(INCLUDE)

LogManager/LogManager.o: LogManager/LogManager.c
	$(CC) $(LDFLAGS) -c -o LogManager/LogManager.o LogManager/LogManager.c $(LDLIBS) $(INCLUDE)

test: $(OBJS_TEST)
	$(CC) $(LDFLAGS) -o Test/test $(SRCS_TEST)

clean:
	$(RM) $(OBJS_MAIN)

distclean: clean
	$(RM) main