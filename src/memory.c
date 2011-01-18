/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

/* public function definitions */

void * mem_alloc(size_t size) {
  return malloc(size);
}

void * mem_realloc(void * p, size_t size) {
  return realloc(p, size);
}

void mem_free(void * p) {
  if(p) { free(p); }
}
