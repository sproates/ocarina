#include <iostream>

#include "lexer.h"
#include "parser.h"

int main(int argc, char** argv) {
  std::cout << "Ocarina" << std::endl;
  ocarina::lexer* lexer = new ocarina::lexer();
  ocarina::parser* parser = new ocarina::parser();
  delete parser;
  delete lexer;
  return 0;
}