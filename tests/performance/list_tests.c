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

/**
 * Run the tests for the list_remove() function.
 */
void _test_remove(void);

/* public function definitions */

void list_tests(void) {
  unsigned int millis;

  printf("Running list performance tests.\n");

  printf("Running list_append() tests.\n");
  millis = time_func(_test_append);
  printf("Test took %d sec %d millis CPU time\n", (int)(millis / 1000), (int)(millis % 1000));

  printf("Running list_remove() tests.\n");
  millis = time_func(_test_remove);
  printf("Test took %d sec %d millis CPU time\n", (int)(millis / 1000), (int)(millis % 1000));

  printf("Completed list tests.\n");
}

/* private function definitions */

void _test_append(void) {
  list * x;
  unsigned int i;
  char * a = "a";

  x = list_new("test");

  for(i = 0; i < 10000; i++) {
    list_append(x, list_new(a));
  }

  list_del(x);
}

void _test_remove(void) {
  list * x, * a, * b, * c , * d;
  unsigned int i;
  char * e = "e";

  x = list_new("test");

  for(i = 0; i < 10000; i++) {
    a = list_new(e);
    b = list_new(e);
    c = list_new(e);
    d = list_new(e);
    list_append(x, a);
    list_append(x, b);
    list_append(x, c);
    list_append(x, d);
    list_remove(x, a);
    list_remove(x, c);
    list_remove(x, b);
    list_remove(x, d);
  }
  list_del(x);
}
