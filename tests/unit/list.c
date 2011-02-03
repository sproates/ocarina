/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file list.c
 * List unit tests.
 */

#include "list.h"
#include "unit_tests.h"

/* public function prototypes */

/**
 * Run the tests for the list functions.
 */
void list_tests(void);

/* public function definitions */

void list_tests(void) {
  list * x, * y;

  printf("Testing list_new()\n");

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

  printf("Testing list_size()\n");

  x = list_new("a");
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
    printf("List has wrong size.\n");
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

  printf("Testing list_append()\n");

  x = list_new("a");
  y = list_new("b");
  if(4 != list_get_allocated() || test_pass()) {
    printf("Should be 4 lists allocated\n");
    test_fail();
    return;
  }
  if(2 != list_get_freed() || test_pass()) {
    printf("Should be 2 lists freed\n");
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
  if(4 != list_get_allocated() || test_pass()) {
    printf("Should be 4 lists allocated\n");
    test_fail();
    return;
  }
  if(4 != list_get_freed() || test_pass()) {
    printf("Should be 4 lists freed\n");
    test_fail();
    return;
  }

  printf("Testing list_prepend()\n");

  x = list_new("a");
  y = list_new("b");
  if(6 != list_get_allocated() || test_pass()) {
    printf("Should be 6 lists allocated\n");
    test_fail();
    return;
  }
  if(4 != list_get_freed() || test_pass()) {
    printf("Should be 4 lists freed\n");
    test_fail();
    return;
  }
  x = list_prepend(x, y);
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


  printf("Testing list_tail()\n");

  x = list_new("a");
  y = list_new("b");
  if(8 != list_get_allocated() || test_pass()) {
    printf("Should be 8 lists allocated\n");
    test_fail();
    return;
  }
  if(6 != list_get_freed() || test_pass()) {
    printf("Should be 6 lists freed\n");
    test_fail();
    return;
  }
  x = list_append(x, y);
  if(y != list_tail(x) || test_pass()) {
    printf("Tail of the list is wrong.\n");
    test_fail();
    return;
  }
  list_del(x);
  if(8 != list_get_allocated() || test_pass()) {
    printf("Should be 8 lists allocated\n");
    test_fail();
    return;
  }
  if(8 != list_get_freed() || test_pass()) {
    printf("Should be 8 lists freed\n");
    test_fail();
    return;
  }

  printf("Testing list_head()\n");

  x = list_new("a");
  y = list_new("b");
  y = list_append(x, y);
  if(10 != list_get_allocated() || test_pass()) {
    printf("Should be 10 lists allocated\n");
    test_fail();
    return;
  }
  if(8 != list_get_freed() || test_pass()) {
    printf("Should be 8 lists freed\n");
    test_fail();
    return;
  }
  if(x != list_head(y) || test_pass()) {
    printf("Head of the list is wrong.\n");
    test_fail();
    return;
  }
  list_del(x);
  if(10 != list_get_allocated() || test_pass()) {
    printf("Should be 10 lists allocated\n");
    test_fail();
    return;
  }
  if(10 != list_get_freed() || test_pass()) {
    printf("Should be 10 lists freed\n");
    test_fail();
    return;
  }

  printf("Testing list_remove()\n");

  printf("Remove tail of list\n");

  x = list_new("a");
  y = list_new("b");
  x = list_append(x, y);
  if(12 != list_get_allocated() || test_pass()) {
    printf("Should be 12 lists allocated\n");
    test_fail();
    return;
  }
  if(10 != list_get_freed() || test_pass()) {
    printf("Should be 10 lists freed\n");
    test_fail();
    return;
  }
  x = list_remove(x, y);
  if(12 != list_get_allocated() || test_pass()) {
    printf("Should be 12 lists allocated\n");
    test_fail();
    return;
  }
  if(11 != list_get_freed() || test_pass()) {
    printf("Should be 11 lists freed\n");
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
  if(12 != list_get_allocated() || test_pass()) {
    printf("Should be 12 lists allocated\n");
    test_fail();
    return;
  }
  if(12 != list_get_freed() || test_pass()) {
    printf("Should be 12 lists freed\n");
    test_fail();
    return;
  }

  printf("Remove head of size n list\n");

  x = list_new("a");
  y = list_new("b");
  x = list_append(x, y);
  if(14 != list_get_allocated() || test_pass()) {
    printf("Should be 14 lists allocated\n");
    test_fail();
    return;
  }
  if(12 != list_get_freed() || test_pass()) {
    printf("Should be 12 lists freed\n");
    test_fail();
    return;
  }
  x = list_remove(x, x);
  if(14 != list_get_allocated() || test_pass()) {
    printf("Should be 14 lists allocated\n");
    test_fail();
    return;
  }
  if(13 != list_get_freed() || test_pass()) {
    printf("Should be 13 lists freed\n");
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
  if(14 != list_get_allocated() || test_pass()) {
    printf("Should be 14 lists allocated\n");
    test_fail();
    return;
  }
  if(13 != list_get_freed() || test_pass()) {
    printf("Should be 13 lists freed\n");
    test_fail();
    return;
  }
  list_del(x);
  if(14 != list_get_allocated() || test_pass()) {
    printf("Should be 14 lists allocated\n");
    test_fail();
    return;
  }
  if(14 != list_get_freed() || test_pass()) {
    printf("Should be 14 lists freed\n");
    test_fail();
    return;
  }

  printf("Remove head of size 1 list\n");

  x = list_new("a");
  if(15 != list_get_allocated() || test_pass()) {
    printf("Should be 15 lists allocated\n");
    test_fail();
    return;
  }
  if(14 != list_get_freed() || test_pass()) {
    printf("Should be 14 lists freed\n");
    test_fail();
    return;
  }
  x = list_remove(x, x);
  if(15 != list_get_allocated() || test_pass()) {
    printf("Should be 15 lists allocated\n");
    test_fail();
    return;
  }
  if(15 != list_get_freed() || test_pass()) {
    printf("Should be 15 lists freed\n");
    test_fail();
    return;
  }
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

  printf("Remove node from middle of list.\n");

  x = list_new("a");
  y = list_new("b");
  x = list_append(x, y);
  x = list_append(x, list_new("c"));
  if(18 != list_get_allocated() || test_pass()) {
    printf("Should be 18 lists allocated\n");
    test_fail();
    return;
  }
  if(15 != list_get_freed() || test_pass()) {
    printf("Should be 15 lists freed\n");
    test_fail();
    return;
  }
  x = list_remove(x, y);
  if(18 != list_get_allocated() || test_pass()) {
    printf("Should be 18 lists allocated\n");
    test_fail();
    return;
  }
  if(16 != list_get_freed() || test_pass()) {
    printf("Should be 16 lists freed\n");
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
  list_del(x);
  if(18 != list_get_allocated() || test_pass()) {
    printf("Should be 18 lists allocated\n");
    test_fail();
    return;
  }
  if(18 != list_get_freed() || test_pass()) {
    printf("Should be 18 lists freed\n");
    test_fail();
    return;
  }

  printf("Misc list tests\n");

  x = list_new("a");
  x = list_append(x, list_new("p"));
  x = list_append(x, list_new("p"));
  x = list_append(x, list_new("l"));
  x = list_append(x, list_new("e"));
  if(23 != list_get_allocated() || test_pass()) {
    printf("Should be 20 lists allocated\n");
    test_fail();
    return;
  }
  if(18 != list_get_freed() || test_pass()) {
    printf("Should be 18 lists freed\n");
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
  if(23 != list_get_allocated() || test_pass()) {
    printf("Should be 23 lists allocated\n");
    test_fail();
    return;
  }
  if(23 != list_get_freed() || test_pass()) {
    printf("Should be 23 lists freed\n");
    test_fail();
    return;
  }

  printf("Completed list tests.\n");
}
