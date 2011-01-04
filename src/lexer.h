#ifndef LEXER_H
#define LEXER_H

#include "string.h"
#include "token.h"
#include <stdio.h>

enum lexer_state {
  LEXER_COMPLETE,
  LEXER_DEFAULT,
  LEXER_ERROR,
  LEXER_IN_IDENTIFIER,
  LEXER_IN_INTEGER,
  LEXER_IN_STRING
};

typedef struct {
  enum lexer_state state;
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
token * lexer_next_token(lexer * lex);

#endif
