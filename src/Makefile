CC = gcc
RM = rm -f
INCLUDES = .
CFLAGS = -W -Wall -Wextra -Werror -Wtraditional -Wundef -Wshadow \
-Wpointer-arith -Wmissing-prototypes -Wredundant-decls -Winline \
-pedantic-errors -std=iso9899:1990 -ansi -I${INCLUDES}
EXE = ocarina.exe

all: ${EXE}

${EXE}: main.o
	$(CC) -o $@ main.o

clean:
	${RM} ${EXE}
	${RM} *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<