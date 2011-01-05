#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void * mem_alloc(size_t size) {
  return malloc(size);
}

void mem_free(void * p) {
  free(p);
}
