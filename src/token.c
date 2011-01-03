#include "token.h"
#include <stdlib.h>
#include <stdio.h>

token * token_new(enum token_type type, string * data) {
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

void token_delete(token * tok) {
  if(NULL != tok) {
    string_delete(tok->data);
    free(tok);
  }
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
    case TOKEN_STRING:
      printf("String");
      break;
    default:
      printf("Unknown");
      break;
  }
  if(NULL != tok->data) {
    printf("\nData: %s", tok->data->data);
  } else {
    printf("\nData: <empty>");
  }
  printf("\n]\n");
}
