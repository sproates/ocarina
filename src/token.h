#ifndef TOKEN_H
#define TOKEN_H

#include "string.h"

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
} token_type;

typedef struct {
  token_type type;
  string * data;
} token;

token * token_new(token_type type, string * data);
void token_print(token * tok);
void token_delete(token * tok);

#endif
