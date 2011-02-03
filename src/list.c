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
  y->prev = x;
  return list_head(x);
}

list * list_prepend(list * x, list * y) {
  return list_append(y, x);
}

list * list_tail(list * x) {
  return (x && x->next) ? list_tail(x->next) : x;
}

list * list_head(list * x) {
  return (x && x->prev) ? list_head(x->prev) : x;
}

list * list_remove(list * x, list * y) {
  list * z = 0;
  if(!x) { return 0; }
  if(x != y) { return list_remove(x->next, y); }
  if(x->next) {
    if(x->prev) {
      z = list_head(_join(x->prev, x->next));
    } else {
      z = list_head(_join(0, x->next));
    }
    x->next = 0;
  } else if(x->prev) {
    z = list_head(_join(x->prev, 0));
  }
  list_del(x);
  return z;
}

unsigned int list_get_allocated(void) {
  return list_allocated;
}

unsigned int list_get_freed(void) {
  return list_freed;
}

/* private function definitions */

static list * _join(list * x, list * y) {
  if(x) { x->next = y; }
  if(y) { y->prev = x; }
  return (x) ? x : y;
}
