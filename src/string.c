/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#include "string.h"
#include "memory.h"
#include <stdio.h>

/* public function definitions */

string * str_new(const char * c) {
  string * s;
  if(0 == (s = mem_alloc(sizeof(s)))) { return 0; }
  if(0 == (s->data = mem_alloc(1024 * sizeof(char)))) { return 0; }
  s->length = 0;
  s->buffer_size = 1024;
  s->data[s->length] = 0;
  return str_add_char(s, c);
}

string * str_add(string * s, char c) {
  if(s->length > s->buffer_size - 2) {
    s->buffer_size += 1024;
    if(0 == (s->data = mem_realloc(s->data, s->buffer_size * sizeof(char)))) { return 0; }
  }
  s->data[s->length++] = c;
  s->data[s->length] = 0;
  return s;
}
string * str_add_str(string * s1, string * s2) {
  return str_add_char(s1, s2->data);
}

string * str_add_char(string * s, const char * c) {
  unsigned int i = 0;
  if(!c) { return s; }
  while(c[i]) { if(0 == str_add(s, c[i++])) { return 0; } }
  return s;
}

void str_del(string * s) {
  if(!s) { return; }
  mem_free(s->data);
  mem_free(s);
}

unsigned int str_eq(string * s1, string * s2) {
  return (s1->length != s2->length) ? 0 : str_eq_char(s1, s2->data);
}

unsigned int str_eq_char(string * s, const char * c) {
  unsigned int i = 0;
  while(i < s->length && 0 != s->data[i++]) {
    if(s->data[i] != c[i]) { return 0; }
  }
  return 1;
}

char str_at(string * s, const unsigned int i) {
  if(i >= (s->length)) { return 0; }
  return s->data[i];
}
