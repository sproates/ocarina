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

  /**
   * The items in the queue.
   */
  list * data;
} queue;

/* public function prototypes */

/**
 * Construct a new queue.
 * @return The newly create queue on success, zero on failure.
 */
queue * q_new(void);

/**
 * Destructs a queue.
 * @param q The queue.
 */
void q_del(queue * q);

/**
 * Add an item to the back of a queue.
 * @param q The queue.
 * @param data The data to add to the queue.
 */
queue * q_push(queue * q, void * data);

/**
 * Get the item at the front of a queue and remove it from the queue.
 * @param q The queue.
 * @return The item at the front of the queue.
 */
void * q_pop(queue * q);

/**
 * Get the item at the front of a queue without removing it from the queue.
 * @param q The queue.
 * @return The item at the front of the queue.
 */
void * q_front(queue * q);

/**
 * Get the number of items in a queue.
 * @param q The queue.
 * @return The number of items.
 */
unsigned int q_size(const queue * q);

/**
 * Get the number of queues that have been allocated.
 * @return The number of allocated queues.
 */
unsigned int q_get_allocated(void);

/**
 * Get the number of queues that have been freed.
 * @return The number of freed queues.
 */
unsigned int q_get_freed(void);

/**
 * Reset the number of queues that have been freed and allocated.
 */
void q_reset_alloc(void);

#endif
