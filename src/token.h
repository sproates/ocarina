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
} tok_type;

typedef struct {
  tok_type type;
  string * data;
} token;

token * tok_new(tok_type type, string * data);
void tok_print(token * tok);
void tok_delete(token * tok);

#endif
