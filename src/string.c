#include "string.h"
#include "memory.h"
#include <stdio.h>

void string_delete(string * s) {
  if(0 != s) {
    mem_free(s->data);
    mem_free(s);
  }
}

string * string_new(void) {
  string * s;

  if(0 == (s = mem_alloc(sizeof(s)))) {
    printf("Failed to allocate space for string!\n");
    return 0;
  }
  if(0 == (s->data = mem_alloc(1024 * sizeof(char)))) {
    printf("Failed to allocate space for string data!\n");
    return 0;
  }
  s->length = 0;
  s->buffer_size = 1024;
  s->data[0] = 0;
  return s;
}

int string_append(string * s, char c) {
  if(s->length > s->buffer_size - 2) {
    printf("String too long\n");
    return 0;
  }
  s->data[s->length++] = c;
  s->data[s->length] = 0;
  return 1;
}
