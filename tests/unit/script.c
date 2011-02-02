/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file script.c
 * Script unit tests.
 */

#include "script.h"
#include "unit_tests.h"

/* public function prototypes */

/**
 * Run the tests for the script functions.
 */
void script_tests(void);

/* public function definitions */

void script_tests(void) {
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
