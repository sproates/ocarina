#ifndef STRING_H
#define STRING_H

/* public structure definitions */

typedef struct {
  char * data;
  unsigned int length;
  unsigned int buffer_size;
} string;

/* public function prototypes */

string * str_new(const char * c);
string * str_add(string * s, char c);
string * str_add_str(string * s1, string * s2);
string * str_add_char(string * s, const char * c);
void str_del(string * s);
unsigned int str_eq(string * s1, string * s2);
unsigned int str_eq_char(string * s, const char * c);
char str_at(string * s, const unsigned int i);

#endif
