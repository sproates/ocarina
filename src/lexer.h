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
} lexer_state;

typedef struct {
  lexer_state state;
  FILE * script_file;
  int position;
  char * buffer;
  int buffer_size;
  string * token_buffer;
  char current_char;
  int max_buffer_size;
} lexer;

lexer * lexer_new(FILE * script_file);
void lexer_delete(lexer * lex);
void lexer_print(lexer * lex);
token * lexer_next(lexer * lex);
lexer * lexer_set_state(lexer * lex, lexer_state state);
lexer * lexer_set_current_char(lexer * lex, const char c);

#endif
