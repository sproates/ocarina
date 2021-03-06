/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

/**
 * @file unit_tests.h
 * A really basic unit test suite.
 */

/* public function prototypes */

/**
 * Indicate that a test has been passed.
 */
unsigned int test_pass(void);

/**
 * Indicate that a test has been failed.
 */
unsigned int test_fail(void);

/**
 * Get the number of tests that have been run.
 */
int test_count(void);

/**
 * Get the number of tests that have been passed.
 */
int pass_count(void);

/**
 * Get the number of tests that have been failed.
 */
int fail_count(void);

/**
 * Entry point for the test suite.
 *
 * @return Zero on success, non-zero if at least one test fails.
 */
int main(void);

#endif
