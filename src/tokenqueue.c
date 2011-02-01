/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file tokenqueue.c
 */

#include "tokenqueue.h"
#include "memory.h"

/* public function definitions */

token_queue * tok_q_new(const unsigned int size) {
  token_queue * q;
  if(0 == (q = mem_alloc(sizeof(* q)))) { return 0; }
  q->max = size;
  q->size = 0;
  return q;
}

void tok_q_del(token_queue * q) {
  if(0 == q) { return; }
  mem_free(q);
}

/* private function definitions */
