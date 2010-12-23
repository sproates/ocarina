CC = gcc
RM = rm -f
INCLUDES = .
CFLAGS = -W -Wall -Wextra -I${INCLUDES}
EXE = ocarina.exe

all: ${EXE}

${EXE}: main.o
	$(CC) -o $@ main.o

clean:
	${RM} ${EXE}
	${RM} *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<