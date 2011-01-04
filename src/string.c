#include "string.h"
#include "memory.h"
#include <stdio.h>

void string_delete(string * s) {
  if(0 != s) {
    mem_free(s->data);
    mem_free(s);
  }
}

string * string_new(const char * c) {
  string * s;
  int i;

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
  s->data[s->length] = 0;
  if(c) {
    for(i = 0; c[i]; i++) {
      string_append(s, c[i]);
    }
  }
  return s;
}

int string_append(string * s, char c) {
  char * new_data;
  int i;
  if(s->length > s->buffer_size - 2) {
    printf("String too long, increasing storage\n");
    s->buffer_size += 1024;
    if(0 == (new_data = mem_alloc(s->buffer_size * sizeof(char)))) {
      printf("Failed to allocate additional space for string data\n");
      return 0;
    }
    for(i = 0; i < s->length; i++) {
      new_data[i] = s->data[i];
    }
    mem_free(s->data);
    s->data = new_data;
  }
  s->data[s->length++] = c;
  s->data[s->length] = 0;
  return 1;
}

int string_equals(string * s1, string * s2) {
  if(s1->length != s2->length) {
    return 0;
  }
  return string_equals_char(s1, s2->data);
}

int string_equals_char(string * s, const char * c) {
  int i, same = 1;
  for(i = 0; i < s->length; i++) {
    if(s->data[i] != c[i]) {
      same = 0;
      break;
    }
    if(0 == s->data[i]) {
      break;
    }
  }
  return same;
}
