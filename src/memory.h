#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

void * mem_alloc(size_t size);
void mem_free(void * p);

#endif
