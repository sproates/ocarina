.PHONY: all clean loc rebuild

CC = gcc
RM = rm -f
INCLUDES = .
CFLAGS = -W -Wall -Wextra -Werror -Wundef -Wshadow -Wpointer-arith \
-Wmissing-prototypes -Wredundant-decls -Winline -pedantic-errors \
-std=iso9899:1990 -ansi -I${INCLUDES}
EXE = ./ocarina.exe
TEST_EXE = ./run_tests.exe
LIB_OBJS = string.o token.o lexer.o memory.o script.o

all: ${EXE} ${TEST_EXE}
	${TEST_EXE}

rebuild: clean all

${EXE}: main.o ${LIB_OBJS}
	$(CC) -o $@ main.o ${LIB_OBJS}

${TEST_EXE}: tests.o ${LIB_OBJS}
	$(CC) -o $@ tests.o ${LIB_OBJS}

clean:
	${RM} ${EXE}
	${RM} ${TEST_EXE}
	${RM} *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

tests.o: lexer.h string.h token.h memory.h script.h

lexer.o: lexer.h string.h token.h memory.h script.h

string.o: string.h memory.h

token.o: token.h string.h memory.h

script.o: memory.h string.h

loc:
	find . -name "*.c" -o -name "*.h" | xargs wc -l
