.PHONY: all clean test

COMPILER = g++
ECHO = echo
RM = rm -f
FLEX = flex
EXE = ocarina.exe

all: ${EXE}

${EXE}: src/main.cpp src/lexer.cpp
	${ECHO} Building...
	${COMPILER} -o $@ src/*.cpp

src/lexer.cpp: src/tokens.flex
	${ECHO} Creating lexer...
	${FLEX} -o src/lexer.cpp --c++ src/tokens.flex

clean:
	${ECHO} Cleaning up...
	${RM} src/lexer.cpp
	${RM} *.o
	${RM} ${EXE}

test:
	${ECHO} Testing...