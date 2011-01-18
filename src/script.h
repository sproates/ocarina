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

  /**
   * The name of the file containing the script.
   */
  const char * filename;

  /**
   * The file containing the script.
   */
  FILE * f;

  /**
   * Buffer used while reading the file in chunks.
   */
  char * buf;

  /**
   * The size of the input buffer.
   */
  unsigned int buf_size;

  /**
   * The maximum size of the input buffer.
   */
  unsigned int max_buf;

  /**
   * The position of the current character within the input buffer.
   */
  unsigned int pos;

} file_script;

/**
 * Represents a script that originates as a string.
 */
typedef struct {

  /**
   * The string containing the script.
   */
  string * s;

  /**
   * The current position within the string.
   */
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

  /**
   * String script type.
   */
  string_script * s;

  /**
   * File script type.
   */
  file_script * f;

} script_impl;

/**
 * Represents the abstract concept of a script source.
 */
typedef struct {

  /**
   * The type of script.
   */
  script_type type;

  /**
   * The script implementation in this pseudo-inheritance scheme.
   */
  script_impl * impl;

} script;

/* public function prototypes */

/**
 * Create a new script instance.
 * @param type The type of script.
 * @param source In the case of a file script, this is a filename. In the case
 * of a string script, this is the text of the script.
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
