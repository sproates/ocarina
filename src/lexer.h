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
  LEXER_IN_INTEGER
};

typedef struct {
  enum lexer_state state;
  FILE * script_file;
  const char * filename;
  int line_number;
  int position;
  char * buffer;
  int buffer_size;
  string * token_buffer;
  char current_char;
  int max_buffer_size;
} lexer;

lexer * lexer_new(FILE * script_file, const char * filename, int max_buffer_size);
char lexer_next_char(lexer * lex);
void lexer_print(lexer * lex);
token * lexer_next_token(lexer * lex);
int is_int(char c);
int is_whitespace(char c);

#endif
