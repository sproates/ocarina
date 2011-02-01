/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file unit_tests.c
 * A really basic unit test suite.
 */

#include <stdio.h>
#include "lexer.h"
#include "string.h"
#include "token.h"
#include "memory.h"
#include "script.h"
#include "parser.h"
#include "tokenqueue.h"

/* public function prototypes */

/**
 * Entry point for the test suite.
 *
 * @return Zero on success, non-zero if at least one test fails.
 */
int main(void);

/* private function prototypes */

/**
 * Indicate that a test has been passed.
 */
static void test_pass(void);

/**
 * Indicate that a test has been failed.
 */
static void test_fail(void);

/**
 * Get the number of tests that have been run.
 */
static int test_count(void);

/**
 * Get the number of tests that have been passed.
 */
static int pass_count(void);

/**
 * Get the number of tests that have been failed.
 */
static int fail_count(void);

/**
 * Run the tests for the string functions.
 */
static void string_tests(void);

/**
 * Run the tests for the lexer functions.
 */
static void lexer_tests(void);

/**
 * Run the tests for the script functions.
 */
static void script_tests(void);

/**
 * Run the tests for the parser functions.
 */
static void parser_tests(void);

/**
 * Run the tests for the tokenqueue functions.
 */
static void tokenqueue_tests(void);

/* private variables */

/**
 * The number of tests that have been run.
 */
int number_of_tests = 0;

/**
 * The number of tests that have been passed.
 */
int passed_tests = 0;

/**
 * The number of tests that have been failed.
 */
int failed_tests = 0;

/* public function definitions */

int main(void) {
  string_tests();
  lexer_tests();
  script_tests();
  parser_tests();
  tokenqueue_tests();
  printf("\n\n----------------------------------\n\n");
  printf("Tests: %d\n", test_count());
  printf("Passed: %d\n", pass_count());
  printf("Failed: %d\n", fail_count());
  return (0 != fail_count());
}

/* private function definitions */

static void test_pass(void) {
  number_of_tests++;
  passed_tests++;
}

static void test_fail(void) {
  number_of_tests++;
  failed_tests++;
}

static int test_count(void) {
  return number_of_tests;
}

static int fail_count(void) {
  return failed_tests;
}

static int pass_count(void) {
  return passed_tests;
}

static void string_tests(void) {
  string * s;
  char c;

  printf("Running string tests...\n");

  printf("str_new()\n");
  s = str_new("test string");
  if(0 == s) {
    printf("Failed to create new string\n");
    test_fail();
    return;
  }
  test_pass();
  if(11 != s->length) {
    printf("String length is incorrect\n");
    test_fail();
    return;
  }
  test_pass();

  printf("str_add()\n");
  if(0 == str_add(s, '!')) {
    printf("Append failed\n");
    test_fail();
    return;
  }
  test_pass();
  if(12 != s->length) {
    printf("String length is incorrect\n");
    test_fail();
  }
  test_pass();

  str_del(s);
  s = str_new("test string 2");
  printf("str_eq()\n");
  if(!str_eq(s, s)) {
    printf("Strings have unequal length\n");
    test_fail();
  }
  test_pass();
  if(!str_eq_char(s, "test string 2")) {
    printf("Strings have unequal length\n");
    test_fail();
  }
  test_pass();
  str_del(s);

  printf("Long strings\n");
  s = str_new("Lorem ipsum dolor sit amet, consectetur adipiscing elit. ");
  str_add_str(s, str_new("Cras iaculis, purus ac rhoncus ornare, diam quam "));
  str_add_str(s, str_new("aliquet nunc, sit amet hendrerit diam augue id "));
  str_add_str(s, str_new("nulla. Ut consequat leo et turpis tempus molestie."));
  str_add_str(s, str_new("  Nam eros mauris, imperdiet id auctor sed, "));
  str_add_str(s, str_new("venenatis sed tellus. Integer semper ullamcorper "));
  str_add_str(s, str_new("risus, ac porttitor libero adipiscing in. "));
  str_add_str(s, str_new("Praesent faucibus gravida augue at mollis. "));
  str_add_str(s, str_new("Maecenas aliquam, lectus malesuada pulvinar "));
  str_add_str(s, str_new("pretium, elit tellus facilisis eros, a mattis "));
  str_add_str(s, str_new("nisl purus quis mauris. Suspendisse sit amet eros "));
  str_add_str(s, str_new("dui, congue fermentum orci. Vivamus non magna vel "));
  str_add_str(s, str_new("nisl imperdiet euismod vel sed elit. Suspendisse "));
  str_add_str(s, str_new("dolor risus, dictum sit amet tempus tincidunt, "));
  str_add_str(s, str_new("ultricies sed diam. Mauris eu diam venenatis enim"));
  str_add_str(s, str_new("  lacinia tempor. Vestibulum id posuere ligula. "));
  str_add_str(s, str_new("Donec ornare dictum lacus, in tempus augue "));
  str_add_str(s, str_new("scelerisque at. Phasellus blandit neque id odio "));
  str_add_str(s, str_new("ullamcorper sit amet imperdiet felis facilisis. "));
  str_add_str(s, str_new("Donec interdum, libero id placerat cursus, elit "));
  str_add_str(s, str_new("augue pharetra risus, varius bibendum lorem nibh "));
  str_add_str(s, str_new("id nibh. Integer rutrum lobortis neque in rutrum. "));
  str_add_str(s, str_new("Fusce sed purus non ligula imperdiet ornare ut ut "));
  str_add_str(s, str_new("velit. Sed vel fermentum lectus. Etiam a sapien "));
  str_add_str(s, str_new("quis justo vestibulum lacinia. Vestibulum ante "));
  str_add_str(s, str_new("ipsum primis in faucibus orci luctus et ultrices "));
  str_add_str(s, str_new("posuere cubilia Curae; Nam congue dictum ornare. "));
  str_add_str(s, str_new("Curabitur nec arcu mauris. Ut pulvinar elementum "));
  str_add_str(s, str_new("orci, non bibendum justo elementum vel. "));
  str_add_str(s, str_new("Suspendisse ultricies auctor arcu id vestibulum. "));
  str_add_str(s, str_new("Morbi felis eros, faucibus in tempor non, cursus "));
  str_add_str(s, str_new("quis tortor. Suspendisse erat odio, consequat ac "));
  str_add_str(s, str_new("adipiscing in, scelerisque sed magna. Morbi neque "));
  str_add_str(s, str_new("quam, scelerisque vitae aliquam nec, tincidunt "));
  str_add_str(s, str_new("nec metus. Mauris eu lacinia erat. Sed vestibulum "));
  str_add_str(s, str_new("rhoncus leo. Cras vulputate nunc a nisl tincidunt "));
  str_add_str(s, str_new("sed feugiat massa venenatis. Maecenas vel odio "));
  str_add_str(s, str_new("eros, ut bibendum velit. Pellentesque cursus "));
  str_add_str(s, str_new("semper metus, nec accumsan risus eleifend id. "));
  str_add_str(s, str_new("Pellentesque pretium urna et turpis condimentum "));
  str_add_str(s, str_new("ut placerat mauris euismod. Fusce id sapien in "));
  str_add_str(s, str_new("risus tincidunt ullamcorper vitae sit amet nibh. "));
  str_add_str(s, str_new("Vivamus ornare arcu sed sapien dignissim at "));
  str_add_str(s, str_new("pharetra ipsum sollicitudin. Vivamus eleifend "));
  str_add_str(s, str_new("arcu ut augue mollis dapibus. Aliquam id lobortis "));
  str_add_str(s, str_new("risus. Sed eu elit mi. In accumsan vulputate urna,"));
  str_add_str(s, str_new("  ut lacinia nulla mattis ut. Nam tellus justo, "));
  str_add_str(s, str_new("auctor ac adipiscing ut, aliquet at lectus. "));
  str_add_str(s, str_new("Pellentesque augue leo, dapibus ac cursus ac, "));
  str_add_str(s, str_new("vulputate et libero. Morbi imperdiet, dolor et "));
  str_add_str(s, str_new("convallis malesuada, velit justo vulputate libero"));
  str_add_str(s, str_new(", sed volutpat mi metus nec purus. Aenean "));
  str_add_str(s, str_new("pellentesque iaculis nunc amet."));
  
  if(2505 != s->length) {
    printf("Long string has incorrect length: %d\n", s->length);
    test_fail();
  }
  test_pass();
  str_del(s);

  s = str_new("abc");

  printf("str_at()\n");
  if('a' != (c = str_at(s, 0))) {
    printf("Wrong char came back from str_at()\n");
    test_fail();
  }
  test_pass();
  if('b' != (c = str_at(s, 1))) {
    printf("Wrong char came back from str_at(): %c\n", c);
    test_fail();
  }
  test_pass();
  if('c' != (c = str_at(s, 2))) {
    printf("Wrong char came back from str_at(): %c\n", c);
    test_fail();
  }
  test_pass();
  if(0 != (c = str_at(s, 3))) {
    printf("Wrong char came back from str_at()%c\n", c);
    test_fail();
  }
  test_pass();
  if(0 != (c = str_at(s, 1050))) {
    printf("Wrong char came back from str_at()%c\n", c);
    test_fail();
  }
  test_pass();
  str_del(s);

  printf("Completed string tests\n");
}

static void lexer_tests(void) {
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

static void script_tests(void) {
  script * s;
  char c;

  printf("Running script tests...\n");

  printf("scr_new() (file type)\n");
  if(0 == (s = scr_new(SCR_FILE, "test.oca"))) {
    printf("Failed to create a new script\n");
    test_fail();
    return;
  }
  test_pass();

  printf("scr_nextr()\n");
  if('1' != (c = scr_next(s))) {
    printf("scr_next() returned the wrong char\n");
    test_fail();
  }
  test_pass();
  scr_del(s);

  printf("scr_new() (string type)\n");
  if(0 == (s = scr_new(SCR_STR, "abc"))) {
    printf("Failed to create a new script\n");
    test_fail();
    return;
  }
  test_pass();

  printf("scr_next()\n");
  if('a' != (c = scr_next(s))) {
    printf("scr_next() returned the wrong char\n");
    test_fail();
  }
  test_pass();
  if('b' != (c = scr_next(s))) {
    printf("scr_next() returned the wrong char\n");
    test_fail();
  }
  test_pass();
  if('c' != (c = scr_next(s))) {
    printf("scr_next() returned the wrong char\n");
    test_fail();
  }
  test_pass();
  if(EOF != (c = scr_next(s))) {
    printf("scr_next() returned the wrong char\n");
    test_fail();
  }
  test_pass();
  scr_del(s);
}

static void parser_tests(void) {
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

static void tokenqueue_tests(void) {
  token_queue * q;

  printf("tok_q_new()\n");
  if(0 == (q = tok_q_new(10))) {
    printf("Failed to create token queue.\n");
    test_fail();
    return;
  }
  test_pass();
  if(10 != q->max) {
    printf("Token queue capacity is incorrect.\n");
    test_fail();
  }
  test_pass();
  tok_q_del(q);

  printf("Completed token queue tests.\n");
}
