/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef TOKEN_H
#define TOKEN_H

/**
 * @file token.h
 * Functions relating to tokens in the Ocarina language.
 */

#include "string.h"

/**
 * The set of possible states for a token.
 */
typedef enum {
  TOK_CL_BC,
  TOK_CL_BK,
  TOK_CL_PA,
  TOK_EOF,
  TOK_ERR,
  TOK_ID,
  TOK_INT,
  TOK_KEY,
  TOK_OP_BC,
  TOK_OP_BK,
  TOK_OP_PA,
  TOK_STR
} tok_type;

/**
 * Represents the state of a token emitted by the Ocarina lexer.
 */
typedef struct {

  /**
   * The type of the token.
   */
  tok_type type;

  /**
   * The raw data associated with the token, as parsed from a script source.
   */
  string * data;

} token;

/**
 * Constructs a new token.
 * @param type The type of token to create.
 * @param data The data associated with the token.
 * @return The token on success, 0 on failure.
 */
token * tok_new(tok_type type, string * data);

/**
 * Delete a token.
 * @param tok The token to delete.
 */
void tok_delete(token * tok);

/**
 * Print a representation of a token to standard output.
 * @param tok The token.
 */
void tok_print(token * tok);

#endif
