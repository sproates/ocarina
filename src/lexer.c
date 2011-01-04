#include "lexer.h"
#include "memory.h"
#include "token.h"
#include <stdio.h>

char _lexer_next_char(lexer * lex);
int _is_int(char c);
int _is_whitespace(char c);
int _is_string_delimiter(char c);
int _is_identifier(char c);
int _is_identifier_initial(char c);
int _is_alpha(char c);
int _is_control_character(char c);
int _is_keyword(string * s);
token * _token_control_character(char c);

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
    printf("Failed to allocate space for lexer!\n");
    return 0;
  }
  lex->state = LEXER_DEFAULT;
  lex->script_file = script_file;
  lex->position = 0;
  lex->max_buffer_size = 1024;
  lex->buffer = mem_alloc(lex->max_buffer_size * (sizeof(char)));
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
    mem_free(lex);
  }
}

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
 * Obtains the next token from a lexer.
 *
 * @param lex The lexer from which to obtain a token.
 *
 * @return A token.
 */
token * lexer_next_token(lexer * lex) {
  token * tok;

  switch(lex->state) {
    case LEXER_DEFAULT:
      lex->current_char = _lexer_next_char(lex);
      if(EOF == lex->current_char) {
        lex->state = LEXER_COMPLETE;
        return lexer_next_token(lex);
      } else if(_is_int(lex->current_char)) {
        lex->state = LEXER_IN_INTEGER;
        return lexer_next_token(lex);
      } else if(_is_whitespace(lex->current_char)) {
        return lexer_next_token(lex);
      } else if(_is_string_delimiter(lex->current_char)) {
        lex->state = LEXER_IN_STRING;
        lex->current_char = _lexer_next_char(lex);
        return lexer_next_token(lex);
      } else if(_is_identifier_initial(lex->current_char)) {
        lex->state = LEXER_IN_IDENTIFIER;
        return lexer_next_token(lex);
      } else if(_is_control_character(lex->current_char)) {
        tok = _token_control_character(lex->current_char);
        break;
      } else {
        lex->state = LEXER_ERROR;
        return lexer_next_token(lex);
      }
    case LEXER_IN_INTEGER:
      if(_is_int(lex->current_char)) {
        string_append(lex->token_buffer, lex->current_char);
        lex->current_char = _lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      lex->state = LEXER_DEFAULT;
      tok = token_new(TOKEN_INTEGER, lex->token_buffer);
      lex->token_buffer = string_new(0);
      break;
    case LEXER_IN_IDENTIFIER:
      if(_is_identifier(lex->current_char)) {
        string_append(lex->token_buffer, lex->current_char);
        lex->current_char = _lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      lex->state = LEXER_DEFAULT;
      if(_is_keyword(lex->token_buffer)) {
        tok = token_new(TOKEN_KEYWORD, lex->token_buffer);
      } else {
        tok = token_new(TOKEN_IDENTIFIER, lex->token_buffer);
      }
      lex->token_buffer = string_new(0);
      break;
    case LEXER_IN_STRING:
      if(!_is_string_delimiter(lex->current_char)) {
        string_append(lex->token_buffer, lex->current_char);
        lex->current_char = _lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      lex->state = LEXER_DEFAULT;
      tok = token_new(TOKEN_STRING, lex->token_buffer);
      lex->token_buffer = string_new(0);
      break;
    case LEXER_ERROR:
      tok = token_new(TOKEN_ERROR, 0);
      break;
    case LEXER_COMPLETE:
    default:
      lex->state = LEXER_COMPLETE;
      tok = token_new(TOKEN_EOF, 0);
      break;
  }
  return tok;
}

void lexer_print(lexer * lex) {
  printf("Lexer {\n");
  printf("\tState: ");
  switch(lex->state) {
    case LEXER_COMPLETE:
      printf("Complete");
      break;
    case LEXER_DEFAULT:
      printf("Default");
      break;
    case LEXER_ERROR:
      printf("Error");
      break;
    default:
      printf("Unknown");
      break;
  }
  printf("\n}\n");
}

int _is_int(char c) {
  return (48 <= c && 57 >= c);
}

int _is_whitespace(char c) {
  return (9 == c || 10 == c || 13 == c || 32 == c);
}

int _is_string_delimiter(char c) {
  return (34 == c);
}

int _is_alpha(char c) {
  return ((65 <= c && 90 >= c) || (97 <= c && 122 >= c));
}

int _is_identifier(char c) {
  return (_is_alpha(c) || _is_int(c) || 95 == c);
}

int _is_identifier_initial(char c) {
  return (_is_alpha(c) || 95 == c);
}

int _is_control_character(char c) {
  return ('(' == c || ')' == c || '[' == c || ']' == c || '{' == c || '}' == c);
}

token * _token_control_character(char c) {
  enum token_type type;
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