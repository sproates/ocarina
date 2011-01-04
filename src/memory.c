#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

size_t total_alloc = 0;

void * mem_alloc(size_t size) {
  void * mem = malloc(size);
  if(0 != mem) {
    total_alloc += size;
    printf("%c[0;31mallocated %d%c[0;37m\n", 27, size, 27);
  }
  return mem;
}

void mem_free(void * p, size_t amount) {
  if(p) {
    if(amount) {
      total_alloc -= amount;
      printf("freed %d\n", amount);
    } else {
      total_alloc -= sizeof(p);
      printf("%c[0;32mfreed %d%c[0;37m\n", 27, sizeof(p), 27);
    }
  }
  free(p);
}

size_t get_allocated_memory(void) {
  return total_alloc;
}
