CC = gcc
RM = rm -f
INCLUDES = .
CFLAGS = -W -Wall -Wextra -Werror -Wundef -Wshadow -Wpointer-arith \
-Wmissing-prototypes -Wredundant-decls -Winline -pedantic-errors \
-std=iso9899:1990 -ansi -I${INCLUDES}
EXE = ocarina.exe

all: ${EXE}

${EXE}: main.o string.o token.o lexer.o
	$(CC) -o $@ *.o

clean:
	${RM} ${EXE}
	${RM} *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: lexer.h token.h

lexer.o: lexer.h string.h token.h

string.o: string.h

token.o: token.h string.h