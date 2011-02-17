/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file performance_tests.c
 * A really basic performance test suite.
 */

#include <stdio.h>
#include <time.h>
#include "performance_tests.h"
#include "list_tests.c"

/* private variables */

/**
 * The number of tests that have been run.
 */
int number_of_tests = 0;

/**
 * The total CPU time of the tests.
 */
unsigned int cpu_time = 0;

/* private function prototypes */

/* public function definitions */

int main(void) {
  printf("\n\n----------------------------------\n\n");
  printf("Performance tests.\n");
  printf("\n\n----------------------------------\n\n");

  list_tests();

  printf("\n\n----------------------------------\n\n");
  printf("Number of performance tests: %d\n", number_of_tests);
  printf("Completed in %d sec %d millis.\n", (int)(cpu_time / 1000), (int)(cpu_time % 1000));
  printf("\n\n----------------------------------\n\n");
  return 0;
}

unsigned int time_func(void (*func)(void)) {
  unsigned int millis;
  clock_t start = clock();
  (*func)();
  number_of_tests++;
  millis = (unsigned int)((clock() - start) * 1000) / CLOCKS_PER_SEC;
  cpu_time += millis;
  return millis;
}

/* private function definitions */
