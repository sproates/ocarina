/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file list_tests.c
 * List performance tests.
 */

#include "list.h"
#include "performance_tests.h"
#include <stdio.h>

/* public function prototypes */

/**
 * Run the tests for the list functions.
 */
void list_tests(void);

/* private function prototypes */

/**
 * Run the tests for the list_append() function.
 */
void _test_append(void);

/* public function definitions */

void list_tests(void) {
  unsigned int millis;

  printf("Running list performance tests.\n");

  millis = time_func(_test_append);
  printf("Append test took %d sec %d millis CPU time\n", (int)(millis / 1000), (int)(millis % 1000));

  printf("Completed list tests.\n");
}

/* public function definitions */

void _test_append(void) {
  list * x;
  unsigned int i;
  for(i = 0; i < 1000000; i++) {
    list_append(x, list_new("a"));
  }
  list_del(x);
}
