#include "string.h"
#include "memory.h"
#include <stdio.h>

void string_delete(string * s) {
  if(s) {
    mem_free(s->data);
    mem_free(s);
  }
}

string * string_new(const char * c) {
  string * s;
  if(0 == (s = mem_alloc(sizeof(s)))) {
    return 0;
  }
  if(0 == (s->data = mem_alloc(1024 * sizeof(char)))) {
    return 0;
  }
  s->length = 0;
  s->buffer_size = 1024;
  s->data[s->length] = 0;
  return string_append_char(s, c);
}

string * string_append(string * s, char c) {
  if(s->length > s->buffer_size - 2) {
    s->buffer_size += 1024;
    if(0 == (s->data = mem_realloc(s->data, s->buffer_size * sizeof(char)))) {
      return 0;
    }
  }
  s->data[s->length++] = c;
  s->data[s->length] = 0;
  return s;
}

string * string_append_char(string * s, const char * c) {
  int i;
  if(c) {
    for(i = 0; c[i]; i++) {
      if(0 == string_append(s, c[i])) {
        return 0;
      }
    }
  }
  return s;
}

string * string_append_string(string * s1, string * s2) {
  return string_append_char(s1, s2->data);
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
