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
  mem_free(x);
  return;
}

unsigned int list_size(list * x) {
  unsigned int size = 0;
  list * y = x;
  while(y && ++size) { y = y->next; }
  return size;
}

list * list_append(list * x, list * y) {
  x->next = y;
  y->prev = x;
  return x;
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
