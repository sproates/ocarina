# Copyright 2011 Ian Sproates <ian@sproates.net>

.PHONY: all clean rebuild test

CD = cd
CC = gcc
RM = rm -rf
INCLUDES = ../../src
CFLAGS = -W -Wall -Wextra -Werror -Wundef -Wshadow -Wpointer-arith \
-Wmissing-prototypes -Wredundant-decls -Winline -pedantic-errors \
-std=iso9899:1990 -ansi -I${INCLUDES}
EXE = ./run_performance_tests.exe
OBJ_DIR = ../../src
SRC_DIR = ../../src
LIB_OBJS = ${OBJ_DIR}/string.o ${OBJ_DIR}/token.o ${OBJ_DIR}/lexer.o \
${OBJ_DIR}/memory.o ${OBJ_DIR}/script.o ${OBJ_DIR}/parser.o ${OBJ_DIR}/list.o \
${OBJ_DIR}/queue.o ${OBJ_DIR}/stack.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

${EXE}: performance_tests.o ${LIB_OBJS}
	$(CC) -o $@ performance_tests.o ${LIB_OBJS}

performance_tests.o: performance_tests.h

all: ${EXE}
	${EXE}

rebuild: clean all

clean:
	${RM} ${EXE}
	${RM} *.o

LIB_OBJS:
	cd ../../src; ${MAKE}
