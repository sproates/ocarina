/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file unit_tests.c
 * A really basic unit test suite.
 */

#include <stdio.h>
#include "unit_tests.h"
#include "lexer_tests.c"
#include "list_tests.c"
#include "string_tests.c"
#include "script_tests.c"
#include "parser_tests.c"

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

unsigned int test_pass(void) {
  number_of_tests++;
  passed_tests++;
  return 0;
}

unsigned int test_fail(void) {
  number_of_tests++;
  failed_tests++;
  return 0;
}

int test_count(void) {
  return number_of_tests;
}

int fail_count(void) {
  return failed_tests;
}

int pass_count(void) {
  return passed_tests;
}

int main(void) {
  string_tests();
  lexer_tests();
  script_tests();
  parser_tests();
  list_tests();
  printf("\n\n----------------------------------\n\n");
  printf("Tests: %d\n", test_count());
  printf("Passed: %d\n", pass_count());
  printf("Failed: %d\n", fail_count());
  return (0 != fail_count());
}
