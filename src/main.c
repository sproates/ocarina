#include <stdio.h>

#include "token.h"
#include "lexer.h"

#define LEXER_BUFFER_SIZE 1024

void print_usage(const char * exe);
int lexer_test(const char * filename);

int main(int argc, const char ** argv) {
  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  } else {
    return lexer_test(argv[1]);
  }
}

void print_usage(const char * exe) {
  printf("Usage: %s <filename>\n", exe);
}

int lexer_test(const char * filename) {
  FILE * script_file;
  int closure;
  lexer * lex;
  token * tok;

  script_file = fopen(filename, "r");
  if(NULL == script_file) {
    printf("Could not open %s for reading.\n", filename);
    return 1;
  }
  lex = lexer_new(script_file, filename, LEXER_BUFFER_SIZE);
  if(NULL == lex) {
    printf("Unable to start lexing\n");
    return 1;
  }
  while(1) {
    tok = lexer_next_token(lex);
    if(NULL == tok || TOKEN_EOF == tok->type) {
      break;
    }
    token_print(tok);
    token_delete(tok);
  }
  closure = fclose(script_file);
  if(EOF == closure) {
    printf("Failed to close file handle on %s.\n", filename);
    return 1;
  }
  return 0;
}
