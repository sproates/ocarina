/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file queue_tests.c
 * Queue unit tests.
 */

#include "queue.h"
#include "unit_tests.h"
#include <stdio.h>

/* public function prototypes */

/**
 * Run the tests for the list functions.
 */
void queue_tests(void);

/* public function definitions */

void queue_tests(void) {
  queue * q;

  printf("Testing q_new()\n");

  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(1 != q_get_allocated() || test_pass()) {
    printf("Should be 1 queue allocated\n");
    test_fail();
    return;
  }
  if(0 != q_get_freed() || test_pass()) {
    printf("Should be 0 queues freed\n");
    test_fail();
    return;
  }
  q_del(q);
  if(1 != q_get_allocated() || test_pass()) {
    printf("Should be 1 queue allocated\n");
    test_fail();
    return;
  }
  if(1 != q_get_freed() || test_pass()) {
    printf("Should be 1 queue freed\n");
    test_fail();
    return;
  }

  printf("Testing q_push()\n");

  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "a")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(2 != q_get_allocated() || test_pass()) {
    printf("Should be 2 queues allocated\n");
    test_fail();
    return;
  }
  if(1 != q_get_freed() || test_pass()) {
    printf("Should be 1 queue freed\n");
    test_fail();
    return;
  }
  q_del(q);
  if(2 != q_get_allocated() || test_pass()) {
    printf("Should be 2 queues allocated\n");
    test_fail();
    return;
  }
  if(2 != q_get_freed() || test_pass()) {
    printf("Should be 2 queues freed\n");
    test_fail();
    return;
  }

  printf("Testing q_front()\n");

  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(3 != q_get_allocated() || test_pass()) {
    printf("Should be 3 queues allocated\n");
    test_fail();
    return;
  }
  if(2 != q_get_freed() || test_pass()) {
    printf("Should be 2 queues freed\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "a")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('a' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'a' at front of queue.\n");
    test_fail();
    return;
  }
  q_del(q);
  if(3 != q_get_allocated() || test_pass()) {
    printf("Should be 3 queues allocated\n");
    test_fail();
    return;
  }
  if(3 != q_get_freed() || test_pass()) {
    printf("Should be 3 queues freed\n");
    test_fail();
    return;
  }

  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(4 != q_get_allocated() || test_pass()) {
    printf("Should be 4 queues allocated\n");
    test_fail();
    return;
  }
  if(3 != q_get_freed() || test_pass()) {
    printf("Should be 3 queues freed\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "a")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "b")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  q_del(q);
  if(4 != q_get_allocated() || test_pass()) {
    printf("Should be 4 queues allocated\n");
    test_fail();
    return;
  }
  if(4 != q_get_freed() || test_pass()) {
    printf("Should be 4 queues freed\n");
    test_fail();
    return;
  }

  printf("Testing q_size()\n");

  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(5 != q_get_allocated() || test_pass()) {
    printf("Should be 5 queues allocated\n");
    test_fail();
    return;
  }
  if(4 != q_get_freed() || test_pass()) {
    printf("Should be 4 queues freed\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "a")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "b")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size is wrong: %d.\n", q_size(q));
    test_fail();
    return;
  }
  q_del(q);
  if(5 != q_get_allocated() || test_pass()) {
    printf("Should be 5 queues allocated\n");
    test_fail();
    return;
  }
  if(5 != q_get_freed() || test_pass()) {
    printf("Should be 5 queues freed\n");
    test_fail();
    return;
  }

  printf("Testing q_pop()\n");
  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(6 != q_get_allocated() || test_pass()) {
    printf("Should be 6 queues allocated\n");
    test_fail();
    return;
  }
  if(5 != q_get_freed() || test_pass()) {
    printf("Should be 5 queues freed\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "a")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "b")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size is wrong: %d.\n", q_size(q));
    test_fail();
    return;
  }
  if('a' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected 'a' to be popped from queue.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size is wrong: %d.\n", q_size(q));
    test_fail();
    return;
  }
  if('b' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected 'b' to be popped from queue.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size is wrong: %d.\n", q_size(q));
    test_fail();
    return;
  }
  q_del(q);
  if(6 != q_get_allocated() || test_pass()) {
    printf("Should be 6 queues allocated\n");
    test_fail();
    return;
  }
  if(6 != q_get_freed() || test_pass()) {
    printf("Should be 6 queues freed\n");
    test_fail();
    return;
  }

  printf("Testing pop on an empty queue\n");
  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(7 != q_get_allocated() || test_pass()) {
    printf("Should be 7 queues allocated\n");
    test_fail();
    return;
  }
  if(6 != q_get_freed() || test_pass()) {
    printf("Should be 6 queues freed\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Popping an empty queue should return zero.\n");
    test_fail();
    return;
  }
  q_del(q);
  if(7 != q_get_allocated() || test_pass()) {
    printf("Should be 7 queues allocated\n");
    test_fail();
    return;
  }
  if(7 != q_get_freed() || test_pass()) {
    printf("Should be 7 queues freed\n");
    test_fail();
    return;
  }

  printf("Testing front on an empty queue\n");
  if(0 == (q = q_new()) || test_pass()) {
    printf("Failed to create queue.\n");
    test_fail();
    return;
  }
  if(8 != q_get_allocated() || test_pass()) {
    printf("Should be 8 queues allocated\n");
    test_fail();
    return;
  }
  if(7 != q_get_freed() || test_pass()) {
    printf("Should be 7 queues freed\n");
    test_fail();
    return;
  }
  if(0 != q_front(q) || test_pass()) {
    printf("Front of an empty queue should be zero.\n");
    test_fail();
    return;
  }
  q_del(q);
  if(8 != q_get_allocated() || test_pass()) {
    printf("Should be 8 queues allocated\n");
    test_fail();
    return;
  }
  if(8 != q_get_freed() || test_pass()) {
    printf("Should be 8 queues freed\n");
    test_fail();
    return;
  }

  printf("Completed queue tests.\n");
}
