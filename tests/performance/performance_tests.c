/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file performance_tests.c
 * A really basic performance test suite.
 */

#include <stdio.h>
#include <time.h>
#include "performance_tests.h"
#include "list_tests.c"

/* private function prototypes */

/* public function definitions */

int main(void) {
  list_tests();
  return 0;
}

unsigned int time_func(void (*func)(void)) {
  clock_t start = clock();
  (*func)();
  return (int)((clock() - start) * 1000) / CLOCKS_PER_SEC;
}

/* private function definitions */
