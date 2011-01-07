#ifndef LEXER_H
#define LEXER_H

#include "string.h"
#include "token.h"
#include <stdio.h>

typedef enum  {
  LEX_DONE,
  LEX_DEF,
  LEX_ERR,
  LEX_IN_ID,
  LEX_IN_INT,
  LEX_IN_STR
} lex_state;

typedef struct {
  lex_state state;
  FILE * script;
  int pos;
  char * buffer;
  int buf_size;
  string * tok_buf;
  char current_char;
  int max_buf;
} lexer;

lexer * lex_new(FILE * script);
void lex_del(lexer * lex);
token * lex_next(lexer * lex);

#endif
