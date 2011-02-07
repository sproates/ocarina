/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file queue.c
 */

#include "queue.h"
#include "list.h"
#include "memory.h"
#include <stdio.h>

/* private variables */

/**
 * The number of queues that have been allocated.
 */
unsigned int q_allocated = 0;

/**
 * The number of queues that have been freed.
 */
unsigned int q_freed = 0;

/* public function definitions */

queue * q_new() {
  queue * q;
  if(0 == (q = mem_alloc(sizeof(queue)))) { return 0; }
  q->data = 0;
  ++q_allocated;
  return q;
}
void q_del(queue * q) {
  if(!q) { return; }
  list_del(q->data);
  mem_free(q);
  ++q_freed;
}

queue * q_push(queue * q, void * data) {
  if(0 == q->data) {
    if(0 == (q->data = list_new(data))) { return 0; }
  } else {
    list_append(q->data, list_new(data));
  }
  printf("Pushed: %s\n", (char *)list_tail(q->data)->data);
  return q;
}

void * q_pop(queue * q) {
  void * data;
  if(0 == q->data) { return 0; }
  if(0 == (q->data = (list *) list_head(q->data))) { return 0; }
  printf("Got list head: %s\n", (char *)q->data->data);
  data = q->data->data;
  q->data = list_remove(q->data, q->data);
  printf("Popping: %s\n", (char *)data);
  return data;
}

void * q_front(queue * q) {
  list * x;
  if(0 == q->data) { return 0; }
  if(0 == (x = (list * )list_head(q->data))) { return 0; }
  return x->data;
}

unsigned int q_size(const queue * q) {
  return list_size(q->data);
}

unsigned int q_get_allocated(void) {
  return q_allocated;
}

unsigned int q_get_freed(void) {
  return q_freed;
}
