/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef TOKENQUEUE_H
#define TOKENQUEUE_H

/* public structure definitions */

typedef struct {
  int max;
  int size;
} token_queue;

/* public function prototypes */

token_queue * tok_q_new(const int size);
void tok_q_del(token_queue * q);

#endif
