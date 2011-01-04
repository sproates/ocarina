#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

size_t total_alloc = 0;

void * mem_alloc(size_t size) {
  void * mem = malloc(size);
  if(0 != mem) {
    total_alloc += size;
  }
  return mem;
}

void mem_free(void * p) {
  if(p) {
    total_alloc -= sizeof(p);
  }
  free(p);
}

size_t get_allocated_memory(void) {
  return total_alloc;
}
