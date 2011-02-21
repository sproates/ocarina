/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef MEMORY_H
#define MEMORY_H

/**
 * @file memory.h
 * Memory management functions.
 *
 * At the moment these are just wrappers around malloc, free and realloc.
 *
 * They are useful for debugging purposes. When there is a memory issue, we can
 * drop some logging into them, or we can make malloc intermittently fail to
 * simulate out of memory errors.
*/

#include <stdlib.h>

/* public function prototypes */

/**
 * Allocate some heap memory.
 *
 * @param size The amount of memory to allocate.
 *
 * @return A pointer to the allocated memory on success; zero on failure.
 */
void * mem_alloc(size_t size);

/**
 * Free some heap memory that has previously been allocated.
 *
 * @param p The memory to free.
 */
void mem_free(void * p);

/**
 * Alter the size of an allocated heap memory block.
 *
 * @param p A previously allocated heap memory block.
 * @param size The new size of the block.
 *
 * @return A pointer the reallocated memory on success; zero on failure.
 */
void * mem_realloc(void * p, size_t size);

#endif
