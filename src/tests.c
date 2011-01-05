#include <stdio.h>
#include "string.h"
#include "lexer.h"
#include "token.h"
#include "memory.h"

int string_tests(void);
int lexer_tests(void);

int main(void) {
  int string_test_result, lexer_test_result;

  string_test_result = string_tests();
  lexer_test_result = lexer_tests();

  return string_test_result & lexer_test_result;
}

int string_tests(void) {
  printf("Running string tests...\n");
  printf("Completed string tests\n");
  return 0;
}

int lexer_tests(void) {
  FILE * script_file;
  lexer * lex;
  token * tok;

  printf("Running lexer tests...\n");

  if(0 == (script_file = fopen("test.oca", "r"))) {
    printf("Could not open source file for reading.\n");
    return 1;
  }
  if(0 == (lex = lexer_new(script_file))) {
    printf("Unable to start lexing\n");
    return 1;
  }
  while(1) {
    tok = lexer_next_token(lex);
    if(0 == tok || TOKEN_EOF == tok->type) {
      token_delete(tok);
      break;
    }
    token_delete(tok);
  }
  if(EOF == fclose(script_file)) {
    printf("Failed to close file handle on source file.\n");
    return 1;
  }
  lexer_delete(lex);

  printf("Completed lexer tests\n");
  return 0;
}
