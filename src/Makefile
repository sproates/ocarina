# Copyright 2011 Ian Sproates <ian@sproates.net>

.PHONY: all clean loc rebuild

CC = gcc
RM = rm -rf
INCLUDES = .
CFLAGS = -W -Wall -Wextra -Werror -Wundef -Wshadow -Wpointer-arith \
-Wmissing-prototypes -Wredundant-decls -Winline -pedantic-errors \
-std=iso9899:1990 -ansi -I${INCLUDES}
EXE = ./ocarina.exe
LIB_OBJS = string.o token.o lexer.o memory.o script.o parser.o list.o

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

tests.o: tests.c lexer.h string.h token.h memory.h script.h parser.h

lexer.o: lexer.c lexer.h string.h token.h memory.h script.h

string.o: string.c string.h memory.h

token.o: token.c token.h string.h memory.h

script.o: script.c script.h memory.h string.h

parser.o: parser.c parser.h lexer.h

list.o: list.h

loc:
	find . -name "*.c" -o -name "*.h" | xargs wc -l
