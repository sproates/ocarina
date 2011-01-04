#include <stdio.h>
#include "token.h"
#include "lexer.h"
#include "memory.h"

void print_usage(const char * exe);
int lexer_test(const char * filename);
void _l(char * message);

int main(int argc, const char ** argv) {
  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }
  return lexer_test(argv[1]);
}

void print_usage(const char * exe) {
  printf("Usage: %s <filename>\n", exe);
}

int lexer_test(const char * filename) {
  FILE * script_file;
  lexer * lex;
  token * tok;

  _l("starting");
  if(0 == (script_file = fopen(filename, "r"))) {
    printf("Could not open %s for reading.\n", filename);
    return 1;
  }
  if(0 == (lex = lexer_new(script_file))) {
    printf("Unable to start lexing\n");
    return 1;
  }
  _l("created lexer");
  while(1) {
    tok = lexer_next_token(lex);
    _l("got a token");
    if(0 == tok || TOKEN_EOF == tok->type) {
      token_delete(tok);
      break;
    }
    /*token_print(tok);*/
    token_delete(tok);
  }
  if(EOF == fclose(script_file)) {
    printf("Failed to close file handle on %s.\n", filename);
  }
  lexer_delete(lex);
  _l("ending");
  return 0;
}

void _l(char * message) {
  printf("%s\t%d\n", message, get_allocated_memory());
}