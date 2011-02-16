/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file list.c
 */

#include "list.h"
#include "memory.h"

/* private function prototypes */

/**
 * Make two list nodes consecutive.
 * @param x Left hand node.
 * @param y Right hand node.
 * @return The modified list.
 */
static list * _join(list * x, list * y);

/* private variables */

/**
 * The number of list nodes that have been allocated.
 */
unsigned int list_allocated = 0;

/**
 * The number of list nodes that have been freed.
 */
unsigned int list_freed = 0;

/* public function definitions */

list * list_new(void * data) {
  list * x;
  if(0 == (x = mem_alloc(sizeof(list)))) { return 0; }
  x->data = data;
  x->next = x->prev = 0;
  ++list_allocated;
  return x;
}

void list_del(list * x) {
  if(!x) { return; }
  if(x->next) { list_del(x->next); }
  x->prev = x->next = 0;
  mem_free(x);
  ++list_freed;
}

unsigned int list_size(list * x) {
  unsigned int size = 0;
  list * y = x;
  y = list_head(y);
  while(y && ++size) { y = y->next; }
  return size;
}

list * list_append(list * x, list * y) {
  if(!x) { return 0; }
  if(!y) { return x; }
  x = list_tail(x);
  x->next = y;
  return list_head(y->prev = x);
}

list * list_prepend(list * x, list * y) {
  return list_append(y, x);
}

list * list_tail(list * x) {
  list * y;
  if(!x || !x->next) { return x; }
  y = x->next;
  while(y->next) { y = y->next; }
  return y;
}

list * list_head(list * x) {
  list * y;
  if(!x || !x->prev) { return x; }
  y = x->prev;
  while(y->prev) { y = y->prev; }
  return y;
}

list * list_remove(list * x, list * y) {
  list * z = 0;
  if(!x) { return 0; }
  if(x != y) {
    while(x != y && x->next) { x = x->next; }
    if(x != y  && !x->next) { return x; }
  }
  if(x->next) {
    z = list_head(_join((x->prev) ? x->prev : 0, x->next));
    x->next = 0;
  } else if(x->prev) { z = list_head(_join(x->prev, 0)); }
  list_del(x);
  return z;
}

void list_foreach(list * x, void (* func)(void *)) {
  list * y;
  if(0 == x) { return; }
  y = x;
  do {
    (* func)(y->data);
  } while(0 != (y = y->next));
}

unsigned int list_get_allocated(void) {
  return list_allocated;
}

unsigned int list_get_freed(void) {
  return list_freed;
}

void list_reset_alloc(void) {
  list_freed = list_allocated = 0;
}

/* private function definitions */

static list * _join(list * x, list * y) {
  if(x) { x->next = y; }
  if(y) { y->prev = x; }
  return (x) ? x : y;
}
