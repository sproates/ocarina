#include "string.h"
#include <stdlib.h>
#include <stdio.h>

void string_delete(string * s) {
  if(NULL != s) {
    free(s->data);
    free(s);
  }
}

string * string_new(void) {
  string * s;

  s = malloc(sizeof(s));
  if(NULL == s) {
    printf("Failed to allocate space for string!\n");
    return NULL;
  }
  s->data = malloc(1024 * sizeof(char));
  if(NULL == s->data) {
    printf("Failed to allocate space for string data!\n");
    return NULL;
  }
  s->length = 0;
  s->buffer_size = 1024;
  s->data[0] = 0;
  return s;
}

int string_append(string * s, char c) {
  if(s->length > s->buffer_size - 3) {
    printf("String too long\n");
    return 0;
  }
  s->data[s->length++] = c;
  s->data[s->length] = 0;
  return 1;
}
