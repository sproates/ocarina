/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file parser.c
 * Parser unit tests.
 */

#include <stdio.h>
#include "unit_tests.h"
#include "parser.h"
#include "lexer.h"

/* public function prototypes */

/**
 * Run the tests for the parser functions.
 */
void parser_tests(void);

/* public function definitions */

void parser_tests(void) {
  parser * par;
  lexer * lex;

  printf("Running parser tests...\n");

  printf("Created script.\n");
  if(0 == (lex = lex_new_file("test.oca"))) {
    printf("Unable to create lexer.\n");
    return;
  }
  printf("Created lexer.\n");
  printf("par_new()\n");
  if(0 == (par = par_new(lex))) {
    printf("Failed to create parser\n");
    test_fail();
    return;
  }
  test_pass();
  lex_del(lex);
  par_del(par);

  printf("Completed parser tests\n");
}
