/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file list_tests.c
 * List unit tests.
 */

#include "list.h"
#include "unit_tests.h"
#include <stdio.h>

/* public function prototypes */

/**
 * Run the tests for the list functions.
 */
void list_tests(void);

/* private function prototypes */

/**
 * Run the tests for the list_new() function.
 */
void _test_list_new(void);

/**
 * Run the tests for the list_size() function.
 */
void _test_list_size(void);

/**
 * Run the tests for the list_append() function.
 */
void _test_list_append(void);

/**
 * Run the tests for the list_prepend() function.
 */
void _test_list_prepend(void);

/**
 * Run the tests for the list_tail() function.
 */
void _test_list_tail(void);

/**
 * Run the tests for the list_head() function.
 */
void _test_list_head(void);

/**
 * Run the tests for the list_remove() function.
 */
void _test_list_remove(void);

/**
 * Run the tests for the list_foreach() function.
 */
void _test_list_foreach(void);

/**
 * Assume some list data is a char and print it.
 * @param data The list data.
 */
void _print_list_as_char(void * data);

/**
 * Run the composite list tests.
 */
void _test_list_composite(void);

/* public function definitions */

void list_tests(void) {
  printf("Running list tests.\n");

  _test_list_new();
  _test_list_size();
  _test_list_append();
  _test_list_prepend();
  _test_list_head();
  _test_list_tail();
  _test_list_remove();
  _test_list_composite();
  _test_list_foreach();
  
  printf("Completed list tests.\n");
}

/* private function definitions */

void _test_list_new(void) {
  list * x;

  printf("\tTesting list_new()...");

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(0 == (x = list_new("node")) || test_pass()) {
    printf("Failed to create list.\n");
    test_fail();
    return;
  }

  if(1 != list_get_allocated() || test_pass()) {
    printf("Should be 1 list allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  list_del(x);

  if(1 != list_get_allocated() || test_pass()) {
    printf("Should be 1 list allocated\n");
    test_fail();
    return;
  }
  if(1 != list_get_freed() || test_pass()) {
    printf("Should be 1 list freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _test_list_size(void) {
  list * x, * y, * z;

  printf("\tTesting list_size()... ");

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");

  if(1 != list_get_allocated() || test_pass()) {
    printf("Should be 1 list allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(1 != list_size(x) || test_pass()) {
    printf("List has wrong size. Should be 1, but is %d.\n", list_size(x));
    test_fail();
    return;
  }

  list_del(x);

  if(1 != list_get_allocated() || test_pass()) {
    printf("Should be 1 list allocated\n");
    test_fail();
    return;
  }
  if(1 != list_get_freed() || test_pass()) {
    printf("Should be 1 list freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");
  z = list_new("c");
  x = list_append(x, y);
  x = list_append(x, z);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }
  if(3 != list_size(x) || test_pass()) {
    printf("List has wrong size. Should be 3, but is %d.\n", list_size(x));
    test_fail();
    return;
  }

  list_del(x);
  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(3 != list_get_freed() || test_pass()) {
    printf("Should be 3 lists freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _test_list_append(void) {
  list * x, * y;

  printf("\tTesting list_append()... ");

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }  

  x = list_new("a");
  y = list_new("b");

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(0 == (x = list_append(x, y)) || test_pass()) {
    printf("List append failed.\n");
    test_fail();
    return;
  }

  if(2 != list_size(x) || test_pass()) {
    printf("New list has incorrect size.\n");
    test_fail();
    return;
  }

  if('a' != ((char *) x->data)[0] || test_pass()) {
    printf("First item in list should be 'a'.\n");
    test_fail();
    return;
  }
  if('b' != ((char *) x->next->data)[0] || test_pass()) {
    printf("Second item in list should be 'b'.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(2 != list_get_freed() || test_pass()) {
    printf("Should be 2 lists freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  x = list_append(x, list_new("p"));
  x = list_append(x, list_new("p"));
  x = list_append(x, list_new("l"));
  x = list_append(x, list_new("e"));

  if(5 != list_get_allocated() || test_pass()) {
    printf("Should be 5 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  y = list_head(x);

  if(5 != list_size(y) || test_pass()) {
    printf("List is the wrong size: %d.\n", list_size(y));
    test_fail();
    return;
  }
  if('a' != ((char *) y->data)[0] || test_pass()) {
    printf("First item in list should be 'a'.\n");
    test_fail();
    return;
  }
  y = y->next;
  if('p' != ((char *) y->data)[0] || test_pass()) {
    printf("Second item in list should be 'p'.\n");
    test_fail();
    return;
  }
  y = y->next;
  if('p' != ((char *) y->data)[0] || test_pass()) {
    printf("Third item in list should be 'p'.\n");
    test_fail();
    return;
  }
  y = y->next;
  if('l' != ((char *) y->data)[0] || test_pass()) {
    printf("Fourth item in list should be 'l'.\n");
    test_fail();
    return;
  }
  y = y->next;
  if('e' != ((char *) y->data)[0] || test_pass()) {
    printf("Fifth item in list should be 'e'.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(5 != list_get_allocated() || test_pass()) {
    printf("Should be 5 lists allocated\n");
    test_fail();
    return;
  }
  if(5 != list_get_freed() || test_pass()) {
    printf("Should be 5 lists freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _test_list_prepend(void) {
  list * x, * y, * z;

  printf("\tTesting list_prepend()... ");

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_prepend(x, y);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(2 != list_size(x) || test_pass()) {
    printf("New list has incorrect size.\n");
    test_fail();
    return;
  }
  if('b' != ((char *) x->data)[0] || test_pass()) {
    printf("First item in list should be 'b'.\n");
    test_fail();
    return;
  }
  if('a' != ((char *) x->next->data)[0] || test_pass()) {
    printf("Second item in list should be 'a'.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(2 != list_get_freed() || test_pass()) {
    printf("Should be 2 lists freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");
  z = list_new("c");

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_prepend(x, y);
  x = list_prepend(x, z);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(3 != list_size(x) || test_pass()) {
    printf("New list has incorrect size.\n");
    test_fail();
    return;
  }
  if('c' != ((char *) x->data)[0] || test_pass()) {
    printf("First item in list should be 'c'.\n");
    test_fail();
    return;
  }
  if('b' != ((char *) x->next->data)[0] || test_pass()) {
    printf("Second item in list should be 'b'.\n");
    test_fail();
    return;
  }
  if('a' != ((char *) x->next->next->data)[0] || test_pass()) {
    printf("Third item in list should be 'a'.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(3 != list_get_freed() || test_pass()) {
    printf("Should be 3 lists freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _test_list_tail(void) {
  list * x, * y, * z;

  printf("\tTesting list_tail()... ");

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_append(x, y);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(y != list_tail(x) || test_pass()) {
    printf("Tail of the list is wrong.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(2 != list_get_freed() || test_pass()) {
    printf("Should be 2 lists freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");
  z = list_new("c");

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_append(x, y);
  x = list_append(x, z);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(z != list_tail(x) || test_pass()) {
    printf("Tail of the list is wrong.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(3 != list_get_freed() || test_pass()) {
    printf("Should be 3 lists freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _test_list_head(void) {
  list * x, * y, * z;

  printf("\tTesting list_head()... ");

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_append(x, y);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(x != list_head(y) || test_pass()) {
    printf("Head of the list is wrong.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(2 != list_get_freed() || test_pass()) {
    printf("Should be 2 lists freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");
  z = list_new("c");

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_append(x, y);
  x = list_append(x, z);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  if(x != list_head(z) || test_pass()) {
    printf("Head of the list is wrong.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(3 != list_get_freed() || test_pass()) {
    printf("Should be 3 lists freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _test_list_remove(void) {
  list * x, * y, * z;

  printf("\tTesting list_remove()... ");

  /* Remove tail of list */

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");
  x = list_append(x, y);
  x = list_remove(x, y);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(1 != list_get_freed() || test_pass()) {
    printf("Should be 1 list freed\n");
    test_fail();
    return;
  }

  if(1 != list_size(x) || test_pass()) {
    printf("New list size is wrong.\n");
    test_fail();
    return;
  }
  if(list_head(x) != x || test_pass()) {
    printf("List head is wrong.\n");
    test_fail();
    return;
  }
  if(list_tail(x) != x || test_pass()) {
    printf("List tail is wrong.\n");
    test_fail();
    return;
  }
  if('a' != ((char *) x->data)[0] || test_pass()) {
    printf("First item in list should be 'a'.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(2 != list_get_freed() || test_pass()) {
    printf("Should be 2 lists freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  /* Remove head of size n list */

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");
  x = list_append(x, y);
  x = list_remove(x, x);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(1 != list_get_freed() || test_pass()) {
    printf("Should be 1 list freed\n");
    test_fail();
    return;
  }

  if(1 != list_size(x) || test_pass()) {
    printf("List size should be 1\n");
    test_fail();
    return;
  }
  if(0 == x || test_pass()) {
    printf("Removing head of size n list failed.\n");
    test_fail();
    return;
  }
  if('b' != ((char *) x->data)[0] || test_pass()) {
    printf("First item in list should be 'b'.\n");
    test_fail();
    return;
  }

  list_del(x);

  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(2 != list_get_freed() || test_pass()) {
    printf("Should be 2 lists freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  /* Remove head of size 1 list */

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  x = list_remove(x, x);

  if(0 != list_size(x) || test_pass()) {
    printf("New list size is wrong.\n");
    test_fail();
    return;
  }
  if(0 != list_head(x) || test_pass()) {
    printf("List head is wrong.\n");
    test_fail();
    return;
  }
  if(0 != list_tail(x) || test_pass()) {
    printf("List tail is wrong.\n");
    test_fail();
    return;
  }

  if(1 != list_get_allocated() || test_pass()) {
    printf("Should be 1 list allocated\n");
    test_fail();
    return;
  }
  if(1 != list_get_freed() || test_pass()) {
    printf("Should be 1 list freed\n");
    test_fail();
    return;
  }

  list_reset_alloc();

  /* Remove node from middle of list. */

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");
  y = list_new("b");
  z = list_new("c");
  x = list_append(x, y);
  x = list_append(x, z);
  x = list_remove(x, y);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(1 != list_get_freed() || test_pass()) {
    printf("Should be 1 list freed\n");
    test_fail();
    return;
  }

  if('a' != ((char *) x->data)[0] || test_pass()) {
    printf("First item in list should be 'a'.\n");
    test_fail();
    return;
  }
  if('c' != ((char *) x->next->data)[0] || test_pass()) {
    printf("Second item in list should be 'c'.\n");
    test_fail();
    return;
  }
  if(2 != list_size(x) || test_pass()) {
    printf("List size should be 2.\n");
    test_fail();
    return;
  }
  if(x != list_head(x) || test_pass()) {
    printf("List head is wrong\n");
    test_fail();
    return;
  }

  list_del(x);

  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(3 != list_get_freed() || test_pass()) {
    printf("Should be 3 lists freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _test_list_composite(void) {
  printf("\tRunning composite list tests... ");
  printf("\n");
}

void _test_list_foreach(void) {
  list * x;

  printf("\tTesting list_foreach()... ");

  list_reset_alloc();

  if(0 != list_get_allocated() || test_pass()) {
    printf("Should be 0 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }

  x = list_new("a");

  if(1 != list_get_allocated() || test_pass()) {
    printf("Should be 1 list allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }
  if(1 != list_size(x) || test_pass()) {
    printf("List size should be 1.\n");
    test_fail();
    return;
  }

  if(0 == list_append(x, list_new("b")) || test_pass()) {
    printf("Failed to append to list\n");
    test_fail();
    return;
  }
  if(2 != list_get_allocated() || test_pass()) {
    printf("Should be 2 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }
  if(2 != list_size(x) || test_pass()) {
    printf("List size should be 2.\n");
    test_fail();
    return;
  }

  if(0 == list_append(x, list_new("c")) || test_pass()) {
    printf("Failed to append to list\n");
    test_fail();
    return;
  }
  if(3 != list_get_allocated() || test_pass()) {
    printf("Should be 3 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }
  if(3 != list_size(x) || test_pass()) {
    printf("List size should be 3.\n");
    test_fail();
    return;
  }

  if(0 == list_append(x, list_new("d")) || test_pass()) {
    printf("Failed to append to list\n");
    test_fail();
    return;
  }
  if(4 != list_get_allocated() || test_pass()) {
    printf("Should be 4 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }
  if(4 != list_size(x) || test_pass()) {
    printf("List size should be 4.\n");
    test_fail();
    return;
  }

  if(0 == list_append(x, list_new("e")) || test_pass()) {
    printf("Failed to append to list\n");
    test_fail();
    return;
  }
  if(5 != list_get_allocated() || test_pass()) {
    printf("Should be 5 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }
  if(5 != list_size(x) || test_pass()) {
    printf("List size should be 5.\n");
    test_fail();
    return;
  }

  if(0 == list_append(x, list_new("f")) || test_pass()) {
    printf("Failed to append to list\n");
    test_fail();
    return;
  }
  if(6 != list_get_allocated() || test_pass()) {
    printf("Should be 6 lists allocated\n");
    test_fail();
    return;
  }
  if(0 != list_get_freed() || test_pass()) {
    printf("Should be 0 lists freed\n");
    test_fail();
    return;
  }
  if(6 != list_size(x) || test_pass()) {
    printf("List size should be 6.\n");
    test_fail();
    return;
  }

  printf("\n");
  list_foreach(x, &_print_list_as_char);
  
  list_del(x);

  if(6 != list_get_allocated() || test_pass()) {
    printf("Should be 6 lists allocated\n");
    test_fail();
    return;
  }
  if(6 != list_get_freed() || test_pass()) {
    printf("Should be 6 lists freed\n");
    test_fail();
    return;
  }
  printf("\n");
}

void _print_list_as_char(void * data) {
  printf("%s\n", (char *) data);
}
