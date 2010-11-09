#include <iostream>

#include "FlexLexer.h"

int main(int argc, char** argv) {
  std::cout << "Ocarina" << std::endl;

  FlexLexer* lexer = new yyFlexLexer();
  lexer->yylex();
  delete lexer;

  return 0;
}