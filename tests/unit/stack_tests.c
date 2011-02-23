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

  printf("\tTesting stack_new()... ");

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
  printf("\n");
}

void _test_stack_push() {
  stack * s;

  printf("\tTesting stack_push()... ");

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
  printf("\n");
}

void _test_stack_top(void) {
  stack * s;

  printf("\tTesting stack_top()... ");

  stack_reset_alloc();

  s = stack_new();

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

  stack_push(s, "a");

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }
  if('a' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'a'.\n");
    test_fail();
    return;
  }

  stack_push(s, "b");

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }
  if('b' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'b'.\n");
    test_fail();
    return;
  }

  stack_push(s, "c");

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }
  if('c' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'c'.\n");
    test_fail();
    return;
  }

  stack_push(s, "d");

  if(4 != stack_size(s) || test_pass()) {
    printf("Stack size should be 4.\n");
    test_fail();
    return;
  }
  if('d' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'd'.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }
  if('c' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'c'.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }
  if('b' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'b'.\n");
    test_fail();
    return;
  }

  stack_push(s, "e");

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }
  if('e' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'e'.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }
  if('b' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'b'.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }
  if('a' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'a'.\n");
    test_fail();
    return;
  }

  stack_push(s, "f");

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }
  if('f' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'f'.\n");
    test_fail();
    return;
  }


  stack_push(s, "g");

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }
  if('g' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'g'.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }
  if('f' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'f'.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }
  if('a' != (((char *) stack_top(s))[0]) || test_pass()) {
    printf("Item at top of stack should be 'a'.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be 0.\n");
    test_fail();
    return;
  }
  if(0 != stack_top(s) || test_pass()) {
    printf("Item at top of stack should be zero.\n");
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
  printf("\n");
}

void _test_stack_pop(void) {
  stack * s;

  printf("\tTesting stack_pop()... ");

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
  printf("\n");
}

void _test_stack_size(void) {
  stack * s;

  printf("\tTesting stack_size()... ");

  stack_reset_alloc();

  s = stack_new();

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
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_push(s, "a");

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_push(s, "b");

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }

  stack_push(s, "c");

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }

  stack_push(s, "d");

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }

  stack_push(s, "e");

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }

  stack_push(s, "f");

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }

  stack_push(s, "g");

  if(4 != stack_size(s) || test_pass()) {
    printf("Stack size should be 4.\n");
    test_fail();
    return;
  }

  stack_push(s, "h");

  if(5 != stack_size(s) || test_pass()) {
    printf("Stack size should be 5.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(4 != stack_size(s) || test_pass()) {
    printf("Stack size should be 4.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_push(s, "i");

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }

  stack_push(s, "j");

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }

  stack_push(s, "k");

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }

  stack_push(s, "l");

  if(4 != stack_size(s) || test_pass()) {
    printf("Stack size should be 4.\n");
    test_fail();
    return;
  }

  stack_push(s, "m");

  if(5 != stack_size(s) || test_pass()) {
    printf("Stack size should be 5.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(4 != stack_size(s) || test_pass()) {
    printf("Stack size should be 4.\n");
    test_fail();
    return;
  }

  stack_push(s, "n");

  if(5 != stack_size(s) || test_pass()) {
    printf("Stack size should be 5.\n");
    test_fail();
    return;
  }

  stack_push(s, "o");

  if(6 != stack_size(s) || test_pass()) {
    printf("Stack size should be 6.\n");
    test_fail();
    return;
  }

  stack_push(s, "p");

  if(7 != stack_size(s) || test_pass()) {
    printf("Stack size should be 7.\n");
    test_fail();
    return;
  }

  stack_push(s, "q");

  if(8 != stack_size(s) || test_pass()) {
    printf("Stack size should be 8.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(7 != stack_size(s) || test_pass()) {
    printf("Stack size should be 7.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(6 != stack_size(s) || test_pass()) {
    printf("Stack size should be 6.\n");
    test_fail();
    return;
  }

  stack_push(s, "r");

  if(7 != stack_size(s) || test_pass()) {
    printf("Stack size should be 7.\n");
    test_fail();
    return;
  }

  stack_push(s, "s");

  if(8 != stack_size(s) || test_pass()) {
    printf("Stack size should be 8.\n");
    test_fail();
    return;
  }

  stack_push(s, "t");

  if(9 != stack_size(s) || test_pass()) {
    printf("Stack size should be 9.\n");
    test_fail();
    return;
  }

  stack_push(s, "u");

  if(10 != stack_size(s) || test_pass()) {
    printf("Stack size should be 10.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(9 != stack_size(s) || test_pass()) {
    printf("Stack size should be 9.\n");
    test_fail();
    return;
  }

  stack_push(s, "v");

  if(10 != stack_size(s) || test_pass()) {
    printf("Stack size should be 10.\n");
    test_fail();
    return;
  }

  stack_push(s, "w");

  if(11 != stack_size(s) || test_pass()) {
    printf("Stack size should be 11.\n");
    test_fail();
    return;
  }

  stack_push(s, "x");

  if(12 != stack_size(s) || test_pass()) {
    printf("Stack size should be 12.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(11 != stack_size(s) || test_pass()) {
    printf("Stack size should be 11.\n");
    test_fail();
    return;
  }

  stack_push(s, "y");

  if(12 != stack_size(s) || test_pass()) {
    printf("Stack size should be 12.\n");
    test_fail();
    return;
  }

  stack_push(s, "z");

  if(13 != stack_size(s) || test_pass()) {
    printf("Stack size should be 13.\n");
    test_fail();
    return;
  }

  stack_push(s, "0");

  if(14 != stack_size(s) || test_pass()) {
    printf("Stack size should be 14.\n");
    test_fail();
    return;
  }

  stack_push(s, "1");

  if(15 != stack_size(s) || test_pass()) {
    printf("Stack size should be 15.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(14 != stack_size(s) || test_pass()) {
    printf("Stack size should be 14.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(13 != stack_size(s) || test_pass()) {
    printf("Stack size should be 13.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(12 != stack_size(s) || test_pass()) {
    printf("Stack size should be 12.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(11 != stack_size(s) || test_pass()) {
    printf("Stack size should be 11.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(10 != stack_size(s) || test_pass()) {
    printf("Stack size should be 10.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(9 != stack_size(s) || test_pass()) {
    printf("Stack size should be 9.\n");
    test_fail();
    return;
  }

  stack_push(s, "2");

  if(10 != stack_size(s) || test_pass()) {
    printf("Stack size should be 10.\n");
    test_fail();
    return;
  }

  stack_push(s, "3");

  if(11 != stack_size(s) || test_pass()) {
    printf("Stack size should be 11.\n");
    test_fail();
    return;
  }

  stack_push(s, "4");

  if(12 != stack_size(s) || test_pass()) {
    printf("Stack size should be 12.\n");
    test_fail();
    return;
  }

  stack_push(s, "5");

  if(13 != stack_size(s) || test_pass()) {
    printf("Stack size should be 13.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(12 != stack_size(s) || test_pass()) {
    printf("Stack size should be 12.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(11 != stack_size(s) || test_pass()) {
    printf("Stack size should be 11.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(10 != stack_size(s) || test_pass()) {
    printf("Stack size should be 10.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(9 != stack_size(s) || test_pass()) {
    printf("Stack size should be 9.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(8 != stack_size(s) || test_pass()) {
    printf("Stack size should be 8.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(7 != stack_size(s) || test_pass()) {
    printf("Stack size should be 7.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(6 != stack_size(s) || test_pass()) {
    printf("Stack size should be 6.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(5 != stack_size(s) || test_pass()) {
    printf("Stack size should be 5.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(4 != stack_size(s) || test_pass()) {
    printf("Stack size should be 4.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(3 != stack_size(s) || test_pass()) {
    printf("Stack size should be 3.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(2 != stack_size(s) || test_pass()) {
    printf("Stack size should be 2.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(1 != stack_size(s) || test_pass()) {
    printf("Stack size should be 1.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_pop(s);

  if(0 != stack_size(s) || test_pass()) {
    printf("Stack size should be zero.\n");
    test_fail();
    return;
  }

  stack_pop(s);

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
  printf("\n");
}
