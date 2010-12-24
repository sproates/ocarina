#include <stdlib.h>
#include <stdio.h>

enum token_type {
  TOKEN_INTEGER,
  TOKEN_EOF
};

enum lexer_state {
  LEXER_COMPLETE,
  LEXER_DEFAULT,
  LEXER_ERROR
};

typedef struct {
  enum lexer_state state;
  FILE * script_file;
  const char * filename;
} lexer;

typedef struct {
  enum token_type type;
} token;

void print_usage(void);
int run_script(const char * filename);
lexer * lexer_new(FILE * script_file, const char * filename);
void lexer_print(lexer * lex);
token * lexer_next_token(lexer * lex);
token * token_new(enum token_type type);
void token_print(token * tok);

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
  lexer_print(lex);
  while(1) {
    tok = lexer_next_token(lex);
    if(NULL == tok) {
      printf("Got NULL token!\n");
      break;
    }
    if(TOKEN_EOF == tok->type) {
      printf("Got EOF token");
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

  lex = malloc(sizeof * lex);
  if(NULL == lex) {
    printf("Failed to allocate space for lexer!\n");
    return NULL;
  }
  lex->state = LEXER_DEFAULT;
  lex->script_file = script_file;
  lex->filename = filename;
  return lex;
}

token * lexer_next_token(lexer * lex) {
  token * tok;

  if(LEXER_DEFAULT == lex->state) {
    tok = token_new(TOKEN_INTEGER);
    lex->state = LEXER_COMPLETE;
  } else {
    tok = token_new(TOKEN_EOF);
  }
  return tok;
}

token * token_new(enum token_type type) {
  token * tok;

  tok = malloc(sizeof * tok);
  if(NULL == tok) {
    printf("Failed to allocate space for token!\n");
    return NULL;
  }
  tok->type = type;
  return tok;
}

void lexer_print(lexer * lex) {
  printf("Lexer [\n");
  printf("Filename: %s\n", lex->filename);
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
  printf("\n]\n");
}