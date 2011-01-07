#ifndef STRING_H
#define STRING_H

typedef struct {
  char * data;
  int length;
  int buffer_size;
} string;

string * str_new(const char * c);
string * str_add(string * s, char c);
string * str_add_str(string * s1, string * s2);
string * str_add_char(string * s, const char * c);
void str_del(string * s);
int str_eq(string * s1, string * s2);
int str_eq_char(string * s, const char * c);

#endif
