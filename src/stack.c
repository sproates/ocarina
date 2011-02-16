/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file stack.c
 */

#include "stack.h"
#include "list.h"
#include "memory.h"
#include <stdio.h>

/* private variables */

/**
 * The number of stacks that have been allocated.
 */
unsigned int stack_allocated = 0;

/**
 * The number of stacks that have been freed.
 */
unsigned int stack_freed = 0;

/* public function definitions */

stack * stack_new() {
  stack * s;
  if(0 == (s = mem_alloc(sizeof(stack)))) { return 0; }
  s->data = 0;
  ++stack_allocated;
  return s;
}

void stack_del(stack * s) {
  if(!s) { return; }
  list_del(s->data);
  mem_free(s);
  ++stack_freed;
}

stack * stack_push(stack * s, void * data) {
  printf("stack_push() called\n");
  if(0 == s->data) {
    printf("stack data is empty, creating it.\n");
    if(0 == (s->data = list_new(data))) {
      printf("Failed to create new stack data.\n");
      return 0;
    } else {
      printf("Created new stack data.\n");
      if(0 == s->data) {
        printf("But the stack data is still zero.\n");
      } else {
        printf("And the stack data is non-zero.\n");
        printf("list size is now %d\n", list_size(s->data));
      }
      return s;
    }
    /*return (0 != (s->data = list_new(data))) ? s : 0;*/
  }
  printf("Prepending data to stack's list.\n");
  list_prepend(s->data, list_new(data));
  printf("list size is now %d\n", list_size(s->data));
  return s;
}

void * stack_pop(stack * s) {
  void * data = stack_top(s);
  s->data = list_remove(s->data, s->data);
  return data;
}

void * stack_top(stack * s) {
  list * x;
  if(0 == s->data) { return 0; }
  if(0 == (x = (list *)list_head(s->data))) { return 0; }
  return x->data;
}

unsigned int stack_size(const stack * s) {
  if(!s) { return 0; }
  return list_size(s->data);
}

unsigned int stack_get_allocated(void) { return stack_allocated; }

unsigned int stack_get_freed(void) { return stack_freed; }

void stack_reset_alloc(void) {
  stack_freed = stack_allocated = 0;
}
