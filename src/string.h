#ifndef STRING_H
#define STRING_H

typedef struct {
  char * data;
  int length;
  int buffer_size;
} string;

string * string_new(void);
int string_append(string * s, char c);
void string_delete(string * s);

#endif
