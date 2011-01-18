/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef SCRIPT_H
#define SCRIPT_H

/**
 * @file script.h
 * Functions for obtaining Ocarina source code.
 */

#include "string.h"
#include <stdio.h>

/* public structure definitions */

/**
 * Represents a script that originates as a file.
 */
typedef struct {
  const char * filename;
  FILE * f;
  char * buf;
  unsigned int buf_size;
  unsigned int max_buf;
  unsigned int pos;
} file_script;

/**
 * Represents a script that originates as a string.
 */
typedef struct {
  string * s;
  int pos;
} string_script;

/**
 * The set of possible states of a script.
 */
typedef enum {
  SCR_FILE,
  SCR_STR
} script_type;

/**
 * Pseudo-inheritance for script types.
 */
typedef union {
  string_script * s;
  file_script * f;
} script_impl;

/**
 * Represents the abstract concept of a script source.
 */
typedef struct {
  script_type type;
  script_impl * impl;
} script;

/* public function prototypes */

/**
 * Create a new script instance.
 * @param type The type of script.
 * @return A pointer to a script on success, zero on failure.
 */
script * scr_new(const script_type type, const char * source);

/**
 * Destructs a script.
 * @param scr The script to delete.
 */
void scr_del(script * scr);

/**
 * Get the next character from a script.
 * @param scr The script.
 * @return The next character.
 */
char scr_next(script * scr);

#endif
