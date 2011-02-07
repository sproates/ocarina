/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef PERFORMANCE_TESTS_H
#define PERFORMANCE_TESTS_H

/**
 * @file performance_tests.h
 * A really basic performance test suite.
 */

/* public function prototypes */

/**
 * Entry point for the test suite.
 *
 * @return Zero on success, non-zero if at least one test fails.
 */
int main(void);

/**
 * Run a function and determine how many milliseconds of CPU time it took.
 * @param func The function to run.
 * @return The CPU run time of the function in milliseconds.
 */
unsigned int time_func(void (*func)(void));

#endif
