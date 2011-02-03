/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef QUEUE_H
#define QUEUE_H

/**
 * @file queue.h
 * A queue.
 */

#include "list.h"

/* public structure definitions */

/**
 * Represents a bog standard queue.
 */
typedef struct {
  list * data;
} queue;

/* public function prototypes */

queue * q_push(queue * q, void * data);

void * q_pop(queue * q);

void * q_front(queue * q);

unsigned int q_size(const queue * q);

#endif
