/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file list.c
 */

#include "list.h"
#include "memory.h"
#include <stdio.h>

/* public function definitions */

list * list_new(void * data) {
  list * x;
  if(0 == (x = mem_alloc(sizeof(list)))) { return 0; }
  x->data = data;
  x->next = x->prev = 0;
  return x;
}

void list_del(list * x) {
  if(!x) { return; }
  if(x->next) { list_del(x->next); }
  x->prev = x->next = 0;
  mem_free(x);
}

unsigned int list_size(list * x) {
  unsigned int size = 0;
  list * y = x;
  y = list_head(y);
  while(y && ++size) { y = y->next; }
  return size;
}

list * list_append(list * x, list * y) {
  if(0 == x) { return 0; }
  x = list_tail(x);
  x->next = y;
  y->prev = x;
  return list_head(x);
}

list * list_prepend(list * x, list * y) {
  return list_append(y, x);
}

list * list_tail(list * x) {
  return x->next ? list_tail(x->next) : x;
}

list * list_head(list * x) {
  return x->prev ? list_head(x->prev) : x;
}

list * list_remove(list * x, list * y) {
  list * z = 0;
  if(!x) { return 0; }
  if(x != y) { return list_remove(x->next, y); }
  if(x->next) {
    if(x->prev) {
      /* next AND prev = middle of list */
      z = list_head(x);
      x->prev->next = x->next;
      x->next->prev = x->prev;
      goto end;
    } else {
      /* next NOT prev = head of list */
      z = x->next;
      z->prev = 0;
      goto end;
    }
  } else {
    if(x->prev) {
      /* prev NOT next = tail of list */
      z = x->prev;
      z->next = 0;
      goto end;
    }
  }
end:
  list_del(x);
  return z;
}
