#include "lexer.h"
#include "memory.h"
#include "token.h"
#include <stdio.h>

/* module-private functions */

char _lexer_next_char(lexer * lex);
int _is_int(char c);
int _is_space(char c);
int _is_str_end(char c);
int _is_id(char c);
int _is_id_start(char c);
int _is_alpha(char c);
int _is_ctrl_char(char c);
int _is_keyword(string * s);
token * _token_ctrl_char(char c);
token * _token_new(lexer * lex, token_type type, lexer_state state);
lexer * lexer_advance(lexer * lex);

/**
 * Create a new lexer instance.
 *
 * @param script_file Handle to an open source file.
 *
 * @return A pointer to a lexer on success, zero on failure.
 */
lexer * lexer_new(FILE * script_file) {
  lexer * lex;

  if(0 == (lex = mem_alloc(sizeof(* lex)))) {
    return 0;
  }
  lex->state = LEX_DEF;
  lex->script_file = script_file;
  lex->position = 0;
  lex->max_buffer_size = 1024;
  if(0 == (lex->buffer = mem_alloc(lex->max_buffer_size * (sizeof(char))))) {
    return 0;
  }
  lex->buffer_size = 0;
  lex->token_buffer = string_new(0);
  return lex;
}

/**
 * Destructs a lexer.
 *
 * @param lex The lexer to delete.
 */
void lexer_delete(lexer * lex) {
  if(0 != lex) {
    string_delete(lex->token_buffer);
    mem_free(lex->buffer);
    mem_free(lex);
  }
}

/**
 * Set the state of a lexer.
 *
 * @param lex The lexer.
 * @param state The state.
 *
 * @return The modified lexer.
 */
lexer * lexer_set_state(lexer * lex, lexer_state state) {
  if(lex) {
    lex->state = state;
  }
  return lex;
}

/**
 * Get the next character from a lexer.
 *
 * @param lex The lexer.
 *
 * @return char The next character from the lexer (EOF on end of file).
 */
char _lexer_next_char(lexer * lex) {
  if(0 == lex->buffer_size || lex->position >= lex->buffer_size) {
    lex->buffer_size = fread(lex->buffer, sizeof(char), lex->max_buffer_size, lex->script_file);
    if(0 == lex->buffer_size) {
      return EOF;
    }
  }
  return lex->buffer[lex->position++];
}

/**
 * Set the current char of a lexer.
 *
 * @param lex The lexer.
 * @param c The char.
 *
 * @return The lexer.
 */
lexer * lexer_set_current_char(lexer * lex, const char c) {
  if(lex) {
    lex->current_char = c;
  }
  return lex;
}

/**
 * Create a new token from a lexer, and leave the lexer in a given state.
 *
 * @param lex The lexer.
 * @param type The type of token to create.
 * @param state The state to leave the lexer in.
 *
 * @return The newly created token.
 */
token * _token_new(lexer * lex, token_type type, lexer_state state) {
  token * t;
  if(lex) {
    t = token_new(type, lex->token_buffer);
    lex->token_buffer = string_new(0);
    lexer_set_state(lex, state);
  }
  return t;
}

lexer * lexer_advance(lexer * lex) {
  return lexer_set_current_char(lex, _lexer_next_char(lex));
}

/**
 * Obtains the next token from a lexer.
 *
 * @param lex The lexer from which to obtain a token.
 *
 * @return A token.
 */
token * lexer_next(lexer * lex) {
  switch(lex->state) {
    case LEX_DEF:
      lexer_advance(lex);
      if(EOF == lex->current_char) {
        return lexer_next(lexer_set_state(lex, LEX_DONE));
      } else if(_is_int(lex->current_char)) {
        return lexer_next(lexer_set_state(lex, LEX_IN_INT));
      } else if(_is_space(lex->current_char)) {
        return lexer_next(lex);
      } else if(_is_str_end(lex->current_char)) {
        return lexer_next(lexer_advance(lexer_set_state(lex, LEX_IN_STR)));
      } else if(_is_id_start(lex->current_char)) {
        return lexer_next(lexer_set_state(lex, LEX_IN_ID));
      } else if(_is_ctrl_char(lex->current_char)) {
        return _token_ctrl_char(lex->current_char);
        break;
      } else {
        return lexer_next(lexer_set_state(lex, LEX_ERR));
      }
    case LEX_IN_INT:
      if(_is_int(lex->current_char)) {
        if(0 == string_append(lex->token_buffer, lex->current_char)) {
          return lexer_next(lexer_set_state(lex, LEX_ERR));
        }
        return lexer_next(lexer_advance(lex));
      }
      return _token_new(lex, TOKEN_INTEGER, LEX_DEF);
    case LEX_IN_ID:
      if(_is_id(lex->current_char)) {
        if(0 == string_append(lex->token_buffer, lex->current_char)) {
          return lexer_next(lexer_set_state(lex, LEX_ERR));
        }
        return lexer_next(lexer_advance(lex));
      }
      if(_is_keyword(lex->token_buffer)) {
        return _token_new(lex, TOKEN_KEYWORD, LEX_DEF);
      }
      return _token_new(lex, TOKEN_IDENTIFIER, LEX_DEF);
    case LEX_IN_STR:
      if(!_is_str_end(lex->current_char)) {
        if(0 == string_append(lex->token_buffer, lex->current_char)) {
          return lexer_next(lexer_set_state(lex, LEX_ERR));
        }
        return lexer_next(lexer_advance(lex));
      }
      return _token_new(lex, TOKEN_STRING, LEX_ERR);
    case LEX_ERR:
      return _token_new(lex, TOKEN_ERROR, LEX_DEF);
    case LEX_DONE:
    default:
      return _token_new(lex, TOKEN_EOF, LEX_DONE);
  }
  return 0;
}

/**
 * Print a representation of a lexer to stdout.
 *
 * @param lex The lexer.
 */
void lexer_print(lexer * lex) {
  printf("Lexer {\n");
  printf("\tState: ");
  switch(lex->state) {
    case LEX_DONE:
      printf("Complete");
      break;
    case LEX_DEF:
      printf("Default");
      break;
    case LEX_ERR:
      printf("Error");
      break;
    default:
      printf("Unknown");
      break;
  }
  printf("\n}\n");
}

int _is_int(char c) {
  return ('0' <= c && '9' >= c);
}

int _is_space(char c) {
  return ('\t' == c || '\r' == c || '\n' == c || ' ' == c);
}

int _is_str_end(char c) {
  return (34 == c);
}

int _is_alpha(char c) {
  return (('A' <= c && 'Z' >= c) || ('a' <= c && 'z' >= c));
}

int _is_id(char c) {
  return (_is_alpha(c) || _is_int(c) || '_' == c);
}

int _is_id_start(char c) {
  return (_is_alpha(c) || '_' == c);
}

int _is_ctrl_char(char c) {
  return ('(' == c || ')' == c || '[' == c || ']' == c || '{' == c || '}' == c);
}

token * _token_ctrl_char(char c) {
  token_type type;
  switch(c) {
    case '}':
      type = TOKEN_CLOSE_BRACE;
      break;
    case ']':
      type = TOKEN_CLOSE_BRACKET;
      break;
    case ')':
      type = TOKEN_CLOSE_PARENTHESIS;
      break;
    case '[':
      type = TOKEN_OPEN_BRACKET;
      break;
    case '{':
      type = TOKEN_OPEN_BRACE;
      break;
    case '(':
      type = TOKEN_OPEN_PARENTHESIS;
      break;
    default:
      type = TOKEN_ERROR;
      break;
  }
  return token_new(type, 0);
}

int _is_keyword(string * s) {
  return (string_equals_char(s, "if") || string_equals_char(s, "for"));
}