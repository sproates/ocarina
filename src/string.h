/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef STRING_H
#define STRING_H

/**
 * @file string.h
 * A really basic string library, because I hate string.h.
 */

/* public structure definitions */

/**
 * Represents a common or garden string.
 */
typedef struct {
  char * data;
  unsigned int length;
  unsigned int buffer_size;
} string;

/* public function prototypes */

/**
 * Create a new string from an (optional) character array.
 * @param c (optional) character array to form the initial string.
 * @return string on success, 0 on failure.
 */
string * str_new(const char * c);

/**
 * Append a char to a string.
 * @param s The string.
 * @param c The char.
 * @return The modified string on success, 0 on failure.
 */
string * str_add(string * s, char c);

/**
 * Append on string to another.
 * @param s1 The string to be append to.
 * @param s2 The string to be appended from.
 * @return The modified string on success, 0 on failure.
 */
string * str_add_str(string * s1, string * s2);

/**
 * Append a char array to a string.
 * @param s The string.
 * @param c The char array.
 * @return The modified string on success, 0 on failure.
 */
string * str_add_char(string * s, const char * c);

/**
 * Delete a string.
 * @param s String to delete.
 */
void str_del(string * s);

/**
 * Compare two strings for equality in terms of their data.
 * @param s1 A string to compare.
 * @param s2 A string to compare.
 * @return 1 if the strings match, 0 if they don't.
 */
unsigned int str_eq(string * s1, string * s2);

/**
 * Compare a string with a char array for equality in terms of their data.
 * @param s The string.
 * @param c The char array.
 * @return 1 if they are equal, 0 if they are not.
 */
unsigned int str_eq_char(string * s, const char * c);

/**
 * Get the char at a specific position in a string.
 * @param s The string.
 * @param i The position;
 * return A char if the position is valid, 0 otherwise.
 */
char str_at(string * s, const unsigned int i);

#endif
