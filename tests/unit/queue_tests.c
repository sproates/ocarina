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

/* private function prototypes */

/**
 * Run the tests for the q_new() function.
 */
void _test_q_new(void);

/**
 * Run the tests for the q_push() function.
 */
void _test_q_push(void);

/**
 * Run the tests for the q_front() function.
 */
void _test_q_front(void);

/**
 * Run the tests for the q_size() function.
 */
void _test_q_size(void);

/**
 * Run the tests for the q_pop() function.
 */
void _test_q_pop(void);

/* public function definitions */

void queue_tests(void) {
  printf("Running queue tests.\n");
  _test_q_new();
  _test_q_push();
  _test_q_front();
  _test_q_size();
  _test_q_pop();
  printf("Completed queue tests.\n");
}

/* private function definitions */

void _test_q_new(void) {
  queue * q;

  printf("Testing q_new()\n");

  q_reset_alloc();

  if(0 != q_get_allocated() || test_pass()) {
    printf("Should be 0 queues allocated\n");
    test_fail();
    return;
  }
  if(0 != q_get_freed() || test_pass()) {
    printf("Should be 0 queues freed\n");
    test_fail();
    return;
  }

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
}

void _test_q_push(void) {
  queue * q;

  printf("Testing q_push()\n");

  q_reset_alloc();

  if(0 != q_get_allocated() || test_pass()) {
    printf("Should be 0 queues allocated\n");
    test_fail();
    return;
  }
  if(0 != q_get_freed() || test_pass()) {
    printf("Should be 0 queues freed\n");
    test_fail();
    return;
  }

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

  q_reset_alloc();

  if(0 != q_get_allocated() || test_pass()) {
    printf("Should be 0 queues allocated\n");
    test_fail();
    return;
  }
  if(0 != q_get_freed() || test_pass()) {
    printf("Should be 0 queues freed\n");
    test_fail();
    return;
  }

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
  if(0 == (q = q_push(q, "b")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "c")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "d")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "e")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
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
}

void _test_q_front(void) {
  queue * q;

  printf("Testing q_front()\n");

  q_reset_alloc();

  if(0 != q_get_allocated() || test_pass()) {
    printf("Should be 0 queues allocated\n");
    test_fail();
    return;
  }
  if(0 != q_get_freed() || test_pass()) {
    printf("Should be 0 queues freed\n");
    test_fail();
    return;
  }

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
  if('a' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'a' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "b")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('a' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'a' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "c")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('a' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'a' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == q_pop(q) || test_pass()) {
    printf("Failed to pop an item from the queue.\n");
    test_fail();
    return;
  }
  if('b' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'b' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "d")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('b' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'b' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "e")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('b' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'b' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == q_pop(q) || test_pass()) {
    printf("Failed to pop an item from the queue.\n");
    test_fail();
    return;
  }
  if('c' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'c' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == q_pop(q) || test_pass()) {
    printf("Failed to pop an item from the queue.\n");
    test_fail();
    return;
  }
  if('d' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'd' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == q_pop(q) || test_pass()) {
    printf("Failed to pop an item from the queue.\n");
    test_fail();
    return;
  }
  if('e' != ((char *)q_front(q))[0] || test_pass()) {
    printf("Expected 'e' at front of queue.\n");
    test_fail();
    return;
  }
  if(0 == q_pop(q) || test_pass()) {
    printf("Failed to pop an item from the queue.\n");
    test_fail();
    return;
  }
  if(0 != q_front(q) || test_pass()) {
    printf("Queue should be empty.\n");
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
}

void _test_q_size(void) {
  queue * q;

  printf("Testing q_size()\n");

  q_reset_alloc();

  if(0 != q_get_allocated() || test_pass()) {
    printf("Should be 0 queues allocated\n");
    test_fail();
    return;
  }
  if(0 != q_get_freed() || test_pass()) {
    printf("Should be 0 queues freed\n");
    test_fail();
    return;
  }

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
  
  if(0 == (q = q_push(q, "a")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  
  if(0 == (q = q_push(q, "b")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size should be 2.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "c")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(3 != q_size(q) || test_pass()) {
    printf("Queue size should be 3.\n");
    test_fail();
    return;
  }
  if('a' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'a'.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size should be 2.\n");
    test_fail();
    return;
  }
  if('b' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'b'.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  if('c' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'c'.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "a")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "b")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size should be 2.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "c")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(3 != q_size(q) || test_pass()) {
    printf("Queue size should be 3.\n");
    test_fail();
    return;
  }
  if('a' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'a'.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size should be 2.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "d")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(3 != q_size(q) || test_pass()) {
    printf("Queue size should be 3.\n");
    test_fail();
    return;
  }
  if('b' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'b'.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size should be 2.\n");
    test_fail();
    return;
  }
  if('c' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'c'.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "e")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size should be 2.\n");
    test_fail();
    return;
  }
  if('d' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'd'.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  if('e' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'e'.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "f")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  if('f' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'f'.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "g")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "h")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(2 != q_size(q) || test_pass()) {
    printf("Queue size should be 2.\n");
    test_fail();
    return;
  }
  if('g' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'g'.\n");
    test_fail();
    return;
  }
  if(1 != q_size(q) || test_pass()) {
    printf("Queue size should be 1.\n");
    test_fail();
    return;
  }
  if('h' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'h'.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_size(q) || test_pass()) {
    printf("Queue size should be zero.\n");
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
}

void _test_q_pop(void) {
  queue * q;

  printf("Testing q_pop()\n");

  q_reset_alloc();

  if(0 != q_get_allocated() || test_pass()) {
    printf("Should be 0 queues allocated\n");
    test_fail();
    return;
  }
  if(0 != q_get_freed() || test_pass()) {
    printf("Should be 0 queues freed\n");
    test_fail();
    return;
  }

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
  if(0 == (q = q_push(q, "c")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('a' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'a'.\n");
    test_fail();
    return;
  }
  if('b' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'b'.\n");
    test_fail();
    return;
  }
  if('c' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'c'.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
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
  if(0 == (q = q_push(q, "c")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('a' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'a'.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "d")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('b' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'b'.\n");
    test_fail();
    return;
  }
  if('c' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'c'.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "e")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('d' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'd'.\n");
    test_fail();
    return;
  }
  if('e' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'e'.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "f")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('f' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'f'.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "g")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if(0 == (q = q_push(q, "h")) || test_pass()) {
    printf("Failed to push an item to the queue.\n");
    test_fail();
    return;
  }
  if('g' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'g'.\n");
    test_fail();
    return;
  }
  if('h' != ((char *)q_pop(q))[0] || test_pass()) {
    printf("Expected to pop 'h'.\n");
    test_fail();
    return;
  }
  if(0 != q_pop(q) || test_pass()) {
    printf("Expected to pop zero.\n");
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
}
