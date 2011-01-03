#ifndef TOKEN_H
#define TOKEN_H

#include "string.h"

enum token_type {
  TOKEN_INTEGER,
  TOKEN_EOF,
  TOKEN_IDENTIFIER,
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
