/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef PARSER_H
#define PARSER_H

/**
 * The functions that implement the Ocarina parser.
 */

#include "lexer.h"

/* public structure definitions */

/**
 * The set of possible states for a parser.
 */
typedef enum  {
  PAR_DONE,
  PAR_DEF,
  PAR_ERR
} par_state;

/**
 * Represents the state of a parser capable of forming an IR from
 * Ocarina tokens.
 */
typedef struct {
  par_state state;
  lexer * lex;
} parser;

/* public function prototypes */

/**
 * Create a new parser instance.
 * @param lex A pointer to a lexer instance.
 * @return A pointer to a parser on success, zero on failure.
 */
parser * par_new(lexer * lex);

/**
 * Destructs a parser.
 * @param par The parser to delete.
 */
void par_del(parser * par);

#endif
