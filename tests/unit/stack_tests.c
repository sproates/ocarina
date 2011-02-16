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

/* private function definitions */

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
  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
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
  stack * s;

  printf("Testing stack_pop()\n");

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
  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should 1.\n");
    test_fail();
    return;
  }
  if('a' != (((char *) stack_pop(s))[0]) || test_pass()) {
    printf("Item popped from stack should be 'a'.\n");
    test_fail();
    return;
  }
  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
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

  stack_reset_alloc();

  printf("\n\ntesting multiple push/pop\n\n");

  if(0 != stack_get_allocated() || test_pass()) {
    printf("Should be 0 stacks allocated\n");
    test_fail();
    return;
  }
  if(0 != stack_get_freed() || test_pass()) {
    printf("Should be 0 stacks freed\n");
    test_fail();
    return;
  }
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
  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be 0. It is %d.\n", stack_size(s));
    test_fail();
    return;
  }
  if(0 == (s = stack_push(s, "a")) || test_pass()) {
    printf("Failed to push an item to the stack.\n");
    test_fail();
    return;
  }
  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1. It is %d.\n", stack_size(s));
    test_fail();
    return;
  }
  if(0 == (s = stack_push(s, "b")) || test_pass()) {
    printf("Failed to push an item to the stack.\n");
    test_fail();
    return;
  }
  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2. It is %d.\n", stack_size(s));
    test_fail();
    return;
  }
  if(0 == (s = stack_push(s, "c")) || test_pass()) {
    printf("Failed to push an item to the stack.\n");
    test_fail();
    return;
  }
  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3. It is %d.\n", stack_size(s));
    test_fail();
    return;
  }
  if('c' != (((char *) stack_pop(s))[0]) || test_pass()) {
    printf("Item popped from stack should be 'c'.\n");
    test_fail();
    return;
  }
  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2. It is %d.\n", stack_size(s));
    test_fail();
    return;
  }
  if('b' != (((char *) stack_pop(s))[0]) || test_pass()) {
    printf("Item popped from stack should be 'b'.\n");
    test_fail();
    return;
  }
  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1. It is %d.\n", stack_size(s));
    test_fail();
    return;
  }
  if('a' != (((char *) stack_pop(s))[0]) || test_pass()) {
    printf("Item popped from stack should be 'a'.\n");
    test_fail();
    return;
  }
  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero. It is %d.\n", stack_size(s));
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

void _test_stack_size(void) {

}

