LDFLAGS := -O0 -Wall -Werror -Wextra
LDLIBS := 
CC=gcc
RM=rm -f
INCLUDE= -ILogManager

SRCS_MAIN=main.c LogManager/LogManager.c
OBJS_MAIN=$(subst .c,.o,$(SRCS_MAIN))

SRCS_GAME=#Window/Window.cpp Snake/Snake.cpp
OBJS_GAME=$(subst .cpp,.o,$(SRCS_GAME))

SRCS_WINDOW=#Snake/Snake.cpp
OBJS_WINDOW=$(subst .cpp,.o,$(SRCS_WINDOW))


main: $(OBJS_MAIN)
	$(CC) $(LDFLAGS) -o main $(OBJS_MAIN) $(LDLIBS) $(INCLUDE)

main.o: main.c
	$(CC) $(LDFLAGS) -c -o main.o main.c $(LDLIBS) $(INCLUDE)

LogManager/LogManager.o: LogManager/LogManager.c
	$(CC) $(LDFLAGS) -c -o LogManager/LogManager.o LogManager/LogManager.c $(LDLIBS) $(INCLUDE)


clean:
	$(RM) $(OBJS_MAIN)

distclean: clean
	$(RM) main