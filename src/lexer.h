#ifndef LEXER_H
#define LEXER_H

#include "string.h"
#include "token.h"
#include "script.h"
#include <stdio.h>

/* public structure definitions */

typedef enum  {
  LEX_DONE,
  LEX_DEF,
  LEX_ERR,
  LEX_IN_ESC,
  LEX_IN_ID,
  LEX_IN_INT,
  LEX_IN_STR
} lex_state;

typedef struct {
  lex_state state;
  FILE * script;
  string * tok_buf;
  char current_char;
  script * s;
} lexer;

/* public function prototypes */

lexer * lex_new(script * s);
void lex_del(lexer * lex);
token * lex_next(lexer * lex);

#endif
