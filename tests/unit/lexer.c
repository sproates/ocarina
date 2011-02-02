/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file lexer.c
 * Lexer unit tests.
 */

#include "lexer.h"
#include "script.h"
#include "token.h"

/* public function prototypes */

/**
 * Run the tests for the lexer functions.
 */
void lexer_tests(void);

/* public function definitions */

void lexer_tests(void) {
  script * scr;
  lexer * lex;
  token * tok;

  printf("Running lexer tests...\n");

  if(0 == (scr = scr_new(SCR_FILE, "test.oca"))) {
    printf("Could not create script\n");
    return;
  }
  printf("Created script.\n");
  if(0 == (lex = lex_new_file("test.oca"))) {
    printf("Unable to create lexer.\n");
    return;
  }
  printf("Created lexer.\n");
  while(1) {
    tok = lex_next(lex);
    printf("Got a token.\n");
    if(0 == tok || TOK_EOF == tok->type) {
      printf("Deleting token and exiting lexer.\n");
      break;
    }
    printf("Deleting token.\n");
    tok_delete(tok);
    printf("Token deleted.\n");
    printf("Lexing...\n");
  }
  printf("Finished lexing.\n");
  lex_del(lex);

  printf("Completed lexer tests\n");
}