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
} lexer;

typedef struct {
  enum token_type type;
  char * data;
} token;

void print_usage(void);
int run_script(const char * filename);
lexer * lexer_new(FILE * script_file, const char * filename);
char lexer_next_char(lexer * lex);
void lexer_print(lexer * lex);
token * lexer_next_token(lexer * lex);
token * token_new(enum token_type type, char * data);
void token_print(token * tok);
int is_int(char c);
int is_whitespace(char c);

int main(int argc, const char ** argv) {
  printf("Ocarina\n");
  if(argc < 2) {
    print_usage();
    return 1;
  } else {
    return run_script(argv[1]);
  }
}

void print_usage(void) {
  printf("Usage: ocarina.exe <filename>\n");
}

int run_script(const char * filename) {
  FILE * script_file;
  int closure;
  lexer * lex;
  token * tok;

  script_file = fopen(filename, "r");
  if(NULL == script_file) {
    printf("Could not open %s for reading.\n", filename);
    return 1;
  }
  printf("Running on %s...\n", filename);
  lex = lexer_new(script_file, filename);
  if(NULL == lex) {
    printf("Unable to start lexing\n");
    return 1;
  }
  printf("Starting lexing\n");
  while(1) {
    tok = lexer_next_token(lex);
    if(NULL == tok) {
      printf("Got NULL token!\n");
      break;
    }
    if(TOKEN_EOF == tok->type) {
      printf("Got EOF token\n");
      break;
    }
    token_print(tok);
  }
  closure = fclose(script_file);
  if(EOF == closure) {
    printf("Oddness. Failed to close file handle on %s.\n", filename);
    return 1;
  }
  printf("Exiting normally\n");
  return 0;
}

lexer * lexer_new(FILE * script_file, const char * filename) {
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
  lex->buffer = malloc(LEXER_BUFFER_SIZE * (sizeof(char)));
  lex->buffer_size = 0;
  lex->token_buffer = malloc(LEXER_BUFFER_SIZE * (sizeof(char)));
  lex->token_position = 0;
  return lex;
}

char lexer_next_char(lexer * lex) {
  printf("lexer_next_char\n");
  if(0 == lex->buffer_size || lex->position >= lex->buffer_size) {
    printf("filling empty buffer\n");
    lex->buffer_size = fread(lex->buffer, sizeof(char), LEXER_BUFFER_SIZE, lex->script_file);
    if(0 == lex->buffer_size) {
      printf("buffer empty,returning EOF\n");
      return EOF;
    }
  }
  return lex->buffer[lex->position++];
}

token * lexer_next_token(lexer * lex) {
  token * tok;

  switch(lex->state) {
    case LEXER_DEFAULT:
      printf("in state LEXER_DEFAULT\n");
      lex->current_char = lexer_next_char(lex);
      if(EOF == lex->current_char) {
        printf("EOF found. Moving to LEXER_COMPLETE\n");
        lex->state = LEXER_COMPLETE;
        return lexer_next_token(lex);
      }
      if(is_int(lex->current_char)) {
        printf("int found. Moving to LEXER_IN_INTEGER\n");
        lex->state = LEXER_IN_INTEGER;
        return lexer_next_token(lex);
      }
      if(is_whitespace(lex->current_char)) {
        printf("skipping whitespace\n");
        return lexer_next_token(lex);
      }
      break;
    case LEXER_IN_INTEGER:
      printf("in state LEXER_IN_INTEGER\n");
      if(is_int(lex->current_char)) {
        printf("appending current char to token buffer\n");
        lex->token_buffer[lex->token_position++] = lex->current_char;
        lex->current_char = lexer_next_char(lex);
        return lexer_next_token(lex);
      }
      printf("end of integer, returning token\n");
      lex->token_position = 0;
      lex->state = LEXER_DEFAULT;
      return token_new(TOKEN_INTEGER, lex->token_buffer);
      break;
    case LEXER_COMPLETE:
    default:
      printf("in state LEXER_COMPLETE\n");
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