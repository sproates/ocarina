/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file stack_tests.c
 * Stack unit tests.
 */

#include "stack.h"
#include "unit_tests.h"
#include <stdio.h>

/* public function prototypes */

/**
 * Run the tests for the stack functions.
 */
void stack_tests(void);

/* private function prototypes */

/**
 * Run the tests for the stack_new() function.
 */
void _test_stack_new(void);

/**
 * Run the tests for the stack_push() function.
 */
void _test_stack_push(void);

/**
 * Run the tests for the stack_top function.
 */
void _test_stack_top(void);

/**
 * Run the tests for the stack_pop function.
 */
void _test_stack_pop(void);

/**
 * Run the tests for the stack_size() function.
 */
void _test_stack_size(void);

/* public function definitions */

void stack_tests(void) {

  printf("Running stack tests.\n");

  _test_stack_new();
  _test_stack_push();
  _test_stack_top();
  _test_stack_pop();
  _test_stack_size();

  printf("Completed stack tests.\n");
}

void _test_stack_new() {
  stack * s;

  printf("Testing stack_new()\n");

  stack_reset_alloc();

  if(0 == (s = stack_new()) || test_pass()) {
    printf("Failed to create stack.\n");
    test_fail();
    return;
  }
  if(1 != stack_get_allocated() || test_pass()) {
    printf("Should be 1 stack allocated\n");
    test_fail();
    return;
  }
  if(0 != stack_get_freed() || test_pass()) {
    printf("Should be 0 stacks freed\n");
    test_fail();
    return;
  }
  stack_del(s);
  if(1 != stack_get_allocated() || test_pass()) {
    printf("Should be 1 stack allocated\n");
    test_fail();
    return;
  }
  if(1 != stack_get_freed() || test_pass()) {
    printf("Should be 1 stack freed\n");
    test_fail();
    return;
  }
}

void _test_stack_push() {
  stack * s;

  printf("Testing stack_push()\n");

  stack_reset_alloc();

  if(0 == (s = stack_new()) || test_pass()) {
    printf("Failed to create stack.\n");
    test_fail();
    return;
  }
  if(0 == (s = stack_push(s, "a")) || test_pass()) {
    printf("Failed to push an item to the stack.\n");
    test_fail();
    return;
  }
  if(1 != stack_get_allocated() || test_pass()) {
    printf("Should be 1 stack allocated\n");
    test_fail();
    return;
  }
  if(0 != stack_get_freed() || test_pass()) {
    printf("Should be 0 stacks freed\n");
    test_fail();
    return;
  }
  stack_del(s);
  if(1 != stack_get_allocated() || test_pass()) {
    printf("Should be 1 stack allocated\n");
    test_fail();
    return;
  }
  if(1 != stack_get_freed() || test_pass()) {
    printf("Should be 1 stack freed\n");
    test_fail();
    return;
  }
}

void _test_stack_top(void) {

}

void _test_stack_pop(void) {

}

void _test_stack_size(void) {

}

