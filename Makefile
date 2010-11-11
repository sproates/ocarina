.PHONY: all clean test

COMPILER = g++
ECHO = echo
RM = rm -f
FLEX = flex
BISON = bison
EXE = ocarina.exe

all: ${EXE}

${EXE}: src/main.cpp src/lexer.cpp src/parser.cpp
	${ECHO} Building...
	${COMPILER} -o $@ src/*.cpp

src/lexer.cpp: src/tokens.flex src/parser.hpp
	${ECHO} Creating lexer...
	${FLEX} -o $@ --c++ $^

src/parser.cpp: src/parser.bison
	${ECHO} Creating parser...
	${BISON} -d -o $@ $^

src/parser.hpp: src/parser.cpp

clean:
	${ECHO} Cleaning up...
	${RM} src/lexer.cpp
	${RM} src/parser.cpp
	${RM} src/parser.hpp
	${RM} *.o
	${RM} ${EXE}

test:
	${ECHO} Testing...