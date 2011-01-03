#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

lexer * lexer_new(FILE * script_file, const char * filename, int max_buffer_size) {
  lexer * lex;

  lex = malloc(sizeof(* lex));
  if(NULL == lex) {
    printf("Failed to allocate space for lexer!\n");
    return NULL;
  }
  lex->state = LEXER_DEFAULT;
  lex->script_file = script_file;
  lex->filename = filename;
  lex->line_number = 0;
  lex->position = 0;
  lex->max_buffer_size = max_buffer_size;
  lex->buffer = malloc(lex->max_buffer_size * (sizeof(char)));
  lex->buffer_size = 0;
  lex->token_buffer = string_new();
  return lex;
}

char lexer_next_char(lexer * lex) {
  if(0 == lex->buffer_size || lex->position >= lex->buffer_size) {
    lex->buffer_size = fread(lex->buffer, sizeof(char), lex->max_buffer_size, lex->script_file);
    if(0 == lex->buffer_size) {
      return EOF;
    }
  }
  return lex->buffer[lex->position++];
}

token * lexer_next_token(lexer * lex) {
  token * tok;

  switch(lex->state) {
    case LEXER_DEFAULT:
      lex->current_char = lexer_next_char(lex);
      if(EOF == lex->current_char) {
        lex->state = LEXER_COMPLETE;
        return lexer_next_token(lex);
      }
      if(is_int(lex->current_char)) {
        lex->state = LEXER_IN_INTEGER;
        return lexer_next_token(lex);
      }
      if(is_whitespace(lex->current_char)) {
        return lexer_next_token(lex);
      }
      if(is_string_delimiter(lex->current_char)) {
        lex->state = LEXER_IN_STRING;
        lex->current_char = lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      lex->state = LEXER_ERROR;
      return lexer_next_token(lex);
      break;
    case LEXER_IN_INTEGER:
      if(is_int(lex->current_char)) {
        string_append(lex->token_buffer, lex->current_char);
        lex->current_char = lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      lex->state = LEXER_DEFAULT;
      tok = token_new(TOKEN_INTEGER, lex->token_buffer);
      lex->token_buffer = string_new();
      break;
    case LEXER_IN_STRING:
      if(!is_string_delimiter(lex->current_char)) {
        string_append(lex->token_buffer, lex->current_char);
        lex->current_char = lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      lex->state = LEXER_DEFAULT;
      tok = token_new(TOKEN_STRING, lex->token_buffer);
      lex->token_buffer = string_new();
      break;
    case LEXER_ERROR:
      lex->state = LEXER_COMPLETE;
      return lexer_next_token(lex);
    case LEXER_COMPLETE:
    default:
      lex->state = LEXER_COMPLETE;
      tok = token_new(TOKEN_EOF, NULL);
      break;
  }
  return tok;
}

void lexer_print(lexer * lex) {
  printf("Lexer [\n");
  printf("Filename: %s\n", lex->filename);
  printf("Line: %d\n", lex->line_number);
  printf("Position: %d\n", lex->position);
  printf("State: ");
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
  printf("\n]\n");
}

int is_int(char c) {
  return (48 <= c && 57 >= c);
}

int is_whitespace(char c) {
  return (9 == c || 10 == c || 13 == c || 32 == c);
}

int is_string_delimiter(char c) {
  return ('"' == c);
}
