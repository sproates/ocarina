#include "string.h"
#include "memory.h"
#include <stdio.h>

/* public function definitions */

/**
 * Delete a string.
 *
 * @param s String to delete.
 */
void str_del(string * s) {
  if(s) {
    mem_free(s->data);
    mem_free(s);
  }
}

/**
 * Create a new string from an (optional) character array.
 *
 * @param c (optional) character array to form the initial string.
 *
 * @return string on success, 0 on failure.
 */
string * str_new(const char * c) {
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
  return str_add_char(s, c);
}

/**
 * Append a char to a string.
 *
 * @param s The string.
 * @param c The char.
 *
 * @return The modified string on success, 0 on failure.
 */
string * str_add(string * s, char c) {
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

/**
 * Append a char array to a string.
 *
 * @param s The string.
 * @param c The char array.
 *
 * @return The modified string on success, 0 on failure.
 */
string * str_add_char(string * s, const char * c) {
  int i;
  if(c) {
    for(i = 0; c[i]; i++) {
      if(0 == str_add(s, c[i])) {
        return 0;
      }
    }
  }
  return s;
}

/**
 * Append on string to another.
 *
 * @param s1 The string to be append to.
 * @param s2 The string to be appended from.
 *
 * @return The modified string on success, 0 on failure.
 */
string * str_add_str(string * s1, string * s2) {
  return str_add_char(s1, s2->data);
}

/**
 * Compare two strings for equality in terms of their data.
 *
 * @param s1 A string to compare.
 * @param s2 A string to compare.
 *
 * @return 1 if the strings match, 0 if they don't.
 */
int str_eq(string * s1, string * s2) {
  if(s1->length != s2->length) {
    return 0;
  }
  return str_eq_char(s1, s2->data);
}

/**
 * Compare a string with a char array for equality in terms of their data.
 *
 * @param s The string.
 * @param c The char array.
 *
 * @return 1 if they are equal, 0 if they are not.
 */
int str_eq_char(string * s, const char * c) {
  unsigned int i, same = 1;
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

/**
 * Get the char at a specific position in a string.
 *
 * @param s The string.
 * @param i The position;
 *
 * return A char if the position is valid, 0 otherwise.
 */
char str_at(string * s, const unsigned int i) {
  if(i >= (s->length)) {
    return 0;
  }
  return s->data[i];
}
