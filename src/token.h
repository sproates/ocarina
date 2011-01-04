#ifndef TOKEN_H
#define TOKEN_H

#include "string.h"

enum token_type {
  TOKEN_CLOSE_BRACE,
  TOKEN_CLOSE_BRACKET,
  TOKEN_CLOSE_PARENTHESIS,
  TOKEN_EOF,
  TOKEN_ERROR,
  TOKEN_IDENTIFIER,
  TOKEN_INTEGER,
  TOKEN_OPEN_BRACE,
  TOKEN_OPEN_BRACKET,
  TOKEN_OPEN_PARENTHESIS,
  TOKEN_STRING
};

typedef struct {
  enum token_type type;
  string * data;
} token;

token * token_new(enum token_type type, string * data);
void token_print(token * tok);
void token_delete(token * tok);

#endif
