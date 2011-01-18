/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef LEXER_H
#define LEXER_H

/**
 * @file lexer.h
 * The functions that implement the Ocarina lexical analyser.
 */

#include "string.h"
#include "token.h"
#include "script.h"
#include <stdio.h>

/* public structure definitions */

/**
 * The set of possible states for a lexer.
 */
typedef enum  {
  LEX_DONE,
  LEX_DEF,
  LEX_ERR,
  LEX_IN_ESC,
  LEX_IN_ID,
  LEX_IN_INT,
  LEX_IN_STR
} lex_state;

/**
 * Represents the state of a lexical analyser capable of scanning and
 * tokenizing Ocarina source code.
 */
typedef struct {

  /**
   * The current state of the lexer.
   */
  lex_state state;

  /**
   * Buffer used to collect character data for the current token.
   */
  string * tok_buf;

  /**
   * The character currently being examined.
   */
  char current_char;

  /**
   * The script source from which the lexer obtains characters.
   */
  script * s;

} lexer;

/* public function prototypes */

/**
 * Create a new lexer instance.
 * @param s The script from which to obtain source characters.
 * @return A pointer to a lexer on success, zero on failure.
 */
lexer * lex_new(script * s);

/**
 * Create a new lexer instance from a filename.
 * @param filename Name of a file containing source script.
 * @return A pointer to a lexer on success, zero on failure.
 */
lexer * lex_new_file(const char * filename);

/**
 * Destructs a lexer.
 * @param lex The lexer to delete.
 */
void lex_del(lexer * lex);

/**
 * Obtains the next token from a lexer.
 * @param lex The lexer from which to obtain a token.
 * @return A token.
 */
token * lex_next(lexer * lex);

#endif
