/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef STACK_H
#define STACK_H

/**
 * @file stack.h
 * A stack.
 */

#include "list.h"

/* public structure definitions */

/**
 * Represents a bog standard stack.
 */
typedef struct {

  /**
   * The items on the stack.
   */
  list * data;
} stack;

/* public function prototypes */

/**
 * Construct a new stack.
 * @return The newly create stack on success, zero on failure.
 */
stack * stack_new(void);

/**
 * Destructs a stack.
 * @param s The stack.
 */
void stack_del(stack * s);

/**
 * Add an item to a stack.
 * @param s The stack.
 * @param data The item to add.
 * @return The modified stack.
 */
stack * stack_push(stack * s, void * data);

/**
 * Remove an item from the top of a stack.
 * @param s The stack.
 * @return The item at the top of the stack, or zero if the stack is empty.
 */
void * stack_pop(stack * s);

/**
 * Get the item at the top of a stack without removing it from the sack.
 * @param s The stack.
 * @return The item at the top of the stack, or zero if the stack is empty.
 */
void * stack_top(stack * s);

/**
 * Get the number of items in a stack.
 * @param s The stack.
 * @return The number of items in the stack.
 */
unsigned int stack_size(const stack * s);

/**
 * Get the number of stacks that have been allocated.
 * @return The number of allocated stacks.
 */
unsigned int stack_get_allocated(void);

/**
 * Get the number of stacks that have been freed.
 * @return The number of freed stacks.
 */
unsigned int stack_get_freed(void);

/**
 * Reset the number of stacks that have been freed and allocated.
 */
void stack_reset_alloc(void);

#endif
