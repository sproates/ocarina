.PHONY: all clean test

COMPILER = g++
ECHO = echo
RM = rm
FLEX = flex

all: ocarina

ocarina: lexer.o main.o
	@${ECHO} Building...
	@${COMPILER} -o $@ lexer.o main.o

main.o: src/main.cpp
	@${ECHO} Compiling src/main.cpp...
	@${COMPILER} -o $@ src/main.cpp

lexer.o: src/lexer.cpp
	@${ECHO} Compiling src/lexer.cpp...
	@${COMPILER} -o $@ src/lexer.cpp

src/lexer.cpp: src/tokens.flex
	@${ECHO} Creating lexer...
	@${FLEX} -o src/lexer.cpp --c++ --yyclass=Lexer src/tokens.flex

clean:
	@${ECHO} Cleaning up...
	@${RM} src/lexer.cpp
	@${RM} *.o

test:
	@${ECHO} Testing...