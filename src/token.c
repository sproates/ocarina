#include "token.h"
#include "memory.h"
#include <stdio.h>

token * token_new(enum token_type type, string * data) {
  token * tok;

  if(0 == (tok = mem_alloc(sizeof(* tok)))) {
    return 0;
  }
  tok->type = type;
  tok->data = data;
  return tok;
}

void token_delete(token * tok) {
  printf("token_delete()\n");
  if(0 != tok) {
    string_delete(tok->data);
    mem_free(tok);
  }
}

void token_print(token * tok) {
  printf("Token {\n\tType: ");
  switch(tok->type) {
    case TOKEN_CLOSE_BRACE:
      printf("Close brace");
      break;
    case TOKEN_CLOSE_BRACKET:
      printf("Close bracket");
      break;
    case TOKEN_CLOSE_PARENTHESIS:
      printf("Close parenthesis");
      break;
    case TOKEN_EOF:
      printf("EOF");
      break;
    case TOKEN_ERROR:
      printf("Error");
      break;
    case TOKEN_IDENTIFIER:
      printf("Identifier");
      break;
    case TOKEN_INTEGER:
      printf("Integer");
      break;
    case TOKEN_KEYWORD:
      printf("Keyword");
      break;
    case TOKEN_OPEN_BRACE:
      printf("Open brace");
      break;
    case TOKEN_OPEN_BRACKET:
      printf("Open bracket");
      break;
    case TOKEN_OPEN_PARENTHESIS:
      printf("Open parenthesis");
      break;
    case TOKEN_STRING:
      printf("String");
      break;
    default:
      printf("Unknown");
      break;
  }
  printf("\n\tData: ");
  if(0 != tok->data) {
    printf("%s", tok->data->data);
  } else {
    printf("<empty>");
  }
  printf("\n}\n");
}
