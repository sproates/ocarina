# Copyright 2011 Ian Sproates <ian@sproates.net>

.PHONY: all clean rebuild

CC = gcc
RM = rm -rf
INCLUDES = .
CFLAGS = -W -Wall -Wextra -Werror -Wundef -Wshadow -Wpointer-arith \
-Wmissing-prototypes -Wredundant-decls -Winline -pedantic-errors \
-std=iso9899:1990 -ansi -I${INCLUDES}
EXE = ./ocarina.exe
LIB_OBJS = string.o token.o lexer.o memory.o script.o parser.o list.o stack.o \
queue.o

all: ${EXE}

rebuild: clean all

${EXE}: main.o ${LIB_OBJS}
	$(CC) -o $@ main.o ${LIB_OBJS}

clean:
	${RM} ${EXE}
	${RM} ${TEST_EXE}
	${RM} *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

lexer.o: lexer.h lexer.c string.o token.o memory.o script.o

string.o: string.h string.c memory.o

token.o: token.c token.h string.o memory.o

script.o: script.c script.h memory.o string.o

parser.o: parser.h parser.c lexer.o queue.o

list.o: list.h list.c

queue.o: queue.h queue.c list.o

stack.o: stack.h stack.c list.o
