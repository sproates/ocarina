CXX = g++
LEX = flex
RM = rm -f
YACC = bison
INCLUDES = .
CXXFLAGS = -W -Wall -Wextra -I${INCLUDES}
EXE = ocarina.exe

all: ${EXE}

${EXE}: main.o parser.o lexer.o
	$(CXX) -o $@ main.o parser.o lexer.o

clean:
	${RM} ${EXE}
	${RM} *.o
	${RM} parser.h
	${RM} lexer.cpp
	${RM} parser.cpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: main.cpp parser.h lexer.h

parser.h: parser.cpp

parser.cpp: parser.bison
	$(YACC) -o parser.cpp --defines=parser.h parser.bison

lexer.cpp: lexer.flex
	$(LEX) -o lexer.cpp lexer.flex