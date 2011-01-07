#include "token.h"
#include "memory.h"
#include <stdio.h>

token * token_new(token_type type, string * data) {
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
    case TOK_CL_BC:
      printf("Close brace");
      break;
    case TOK_CL_BK:
      printf("Close bracket");
      break;
    case TOK_CL_PA:
      printf("Close parenthesis");
      break;
    case TOK_EOF:
      printf("EOF");
      break;
    case TOK_ERR:
      printf("Error");
      break;
    case TOK_ID:
      printf("Identifier");
      break;
    case TOK_INT:
      printf("Integer");
      break;
    case TOK_KEY:
      printf("Keyword");
      break;
    case TOK_OP_BC:
      printf("Open brace");
      break;
    case TOK_OP_BK:
      printf("Open bracket");
      break;
    case TOK_OP_PA:
      printf("Open parenthesis");
      break;
    case TOK_STR:
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
