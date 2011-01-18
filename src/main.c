/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file main.c
 */

#include <stdio.h>

/* public function prototypes */

/**
 * Entry point for the main program.
 *
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 *
 * return Zero on success, non-zero on failure.
 */
int main(int argc, const char ** argv);

/* private function prototypes */

/**
 * Print usage information to standard output.
 *
 * @param exe The name of the current executable.
 */
static void print_usage(const char * exe);

/* public function definitions */

int main(int argc, const char ** argv) {
  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }
  return 0;
}

/* private function definitions */

static void print_usage(const char * exe) {
  printf("Usage: %s <filename>\n", exe);
}
