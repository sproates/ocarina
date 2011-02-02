/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file list.c
 * List unit tests.
 */

#include "list.h"
#include "unit_tests.h"

/* public function prototypes */

/**
 * Run the tests for the script functions.
 */
void list_tests(void);

/* public function definitions */

void list_tests(void) {
  list * x, * y;

  printf("list_new()\n");
  if(0 == (x = list_new("node"))) {
    printf("Failed to create list.\n");
    test_fail();
    return;
  }
  test_pass();
  printf("list_del()\n");
  list_del(x);
  printf("list_del didn't SIGSEGV.\n");
  test_pass();

  printf("list_size()\n");
  x = list_new("a");
  if(1 != list_size(x)) {
    printf("List has wrong size.\n");
    test_fail();
    return;
  }
  printf("List has correct size.\n");
  test_pass();

  printf("list_append()\n");
  y = list_new("b");
  if(0 == (x = list_append(x, y))) {
    printf("List append failed.\n");
    test_fail();
    return;
  }
  printf("List appended.\n");
  test_pass();

  printf("Checking new size of list.\n");
  if(2 != list_size(x)) {
    printf("New list has incorrect size.\n");
    test_fail();
    return;
  }
  printf("Appended list has correct size.\n");
  test_pass();

  printf("Checking list contents.\n");
  if('a' != ((char *) x->data)[0]) {
    printf("First item in list should be 'a'.\n");
    test_fail();
    return;
  }
  test_pass();

  if('b' != ((char *) x->next->data)[0]) {
    printf("Second item in list should be 'b'.\n");
    test_fail();
    return;
  }
  test_pass();

  list_del(x);

  printf("list_prepend()\n");
  x = list_new("a");
  y = list_new("b");
  x = list_prepend(x, y);
  if(2 != list_size(x)) {
    printf("New list has incorrect size.\n");
    test_fail();
    return;
  }
  test_pass();

  printf("Checking list contents.\n");
  if('b' != ((char *) x->data)[0]) {
    printf("First item in list should be 'b'.\n");
    test_fail();
    return;
  }
  test_pass();

  if('a' != ((char *) x->next->data)[0]) {
    printf("Second item in list should be 'a'.\n");
    test_fail();
    return;
  }
  test_pass();

  list_del(x);
  x = list_new("a");
  y = list_new("b");
  x = list_append(x, y);

  printf("list_tail()\n");
  if(y != list_tail(x)) {
    printf("Tail of the list is wrong.\n");
    test_fail();
    return;
  }
  test_pass();

  printf("list_head()\n");
  if(x != list_head(y)) {
    printf("Head of the list is wrong.\n");
    test_fail();
    return;
  }
  test_pass();

  list_del(x);
}
