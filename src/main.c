#include <stdlib.h>
#include <stdio.h>

#define LEXER_BUFFER_SIZE 1024

enum token_type {
  TOKEN_INTEGER,
  TOKEN_EOF
};

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
  char * token_buffer;
  int token_position;
  char current_char;
  int max_buffer_size;
} lexer;

typedef struct {
  enum token_type type;
  char * data;
} token;

void print_usage(const char * exe);
int lexer_test(const char * filename);
lexer * lexer_new(FILE * script_file, const char * filename, int max_buffer_size);
char lexer_next_char(lexer * lex);
void lexer_print(lexer * lex);
token * lexer_next_token(lexer * lex);
token * token_new(enum token_type type, char * data);
void token_print(token * tok);
int is_int(char c);
int is_whitespace(char c);

int main(int argc, const char ** argv) {
  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  } else {
    return lexer_test(argv[1]);
  }
}

void print_usage(const char * exe) {
  printf("Usage: %s <filename>\n", exe);
}

int lexer_test(const char * filename) {
  FILE * script_file;
  int closure;
  lexer * lex;
  token * tok;

  script_file = fopen(filename, "r");
  if(NULL == script_file) {
    printf("Could not open %s for reading.\n", filename);
    return 1;
  }
  lex = lexer_new(script_file, filename, LEXER_BUFFER_SIZE);
  if(NULL == lex) {
    printf("Unable to start lexing\n");
    return 1;
  }
  while(1) {
    tok = lexer_next_token(lex);
    if(NULL == tok || TOKEN_EOF == tok->type) {
      break;
    }
    token_print(tok);
  }
  closure = fclose(script_file);
  if(EOF == closure) {
    printf("Failed to close file handle on %s.\n", filename);
    return 1;
  }
  return 0;
}

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
  lex->token_buffer = malloc(lex->max_buffer_size * (sizeof(char)));
  lex->token_position = 0;
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
      lex->state = LEXER_ERROR;
      return lexer_next_token(lex);
      break;
    case LEXER_IN_INTEGER:
      if(is_int(lex->current_char)) {
        lex->token_buffer[lex->token_position++] = lex->current_char;
        lex->current_char = lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      lex->token_position = 0;
      lex->state = LEXER_DEFAULT;
      return token_new(TOKEN_INTEGER, lex->token_buffer);
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

token * token_new(enum token_type type, char * data) {
  token * tok;

  tok = malloc(sizeof * tok);
  if(NULL == tok) {
    printf("Failed to allocate space for token!\n");
    return NULL;
  }
  tok->type = type;
  tok->data = data;
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

void token_print(token * tok) {
  printf("Token [\n");
  switch(tok->type) {
    case TOKEN_INTEGER:
      printf("Integer");
      break;
    case TOKEN_EOF:
      printf("EOF");
      break;
    default:
      printf("Unknown");
      break;
  }
  if(NULL != tok->data) {
    printf("\nData: %s", tok->data);
  }
  printf("\n]\n");
}

int is_int(char c) {
  return (48 <= c && 57 >= c);
}

int is_whitespace(char c) {
  return (9 == c || 10 == c || 13 == c || 32 == c);
}