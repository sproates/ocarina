#ifndef STRING_H
#define STRING_H

typedef struct {
  char * data;
  int length;
  int buffer_size;
} string;

string * string_new(const char * c);
string * string_append(string * s, char c);
string * string_append_string(string * s1, string * s2);
string * string_append_char(string * s, const char * c);
void string_delete(string * s);
int string_equals(string * s1, string * s2);
int string_equals_char(string * s, const char * c);

#endif
