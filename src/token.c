#include "token.h"
#include "memory.h"
#include <stdio.h>

/* public function definitions */

/**
 * Constructs a new token.
 * @param type The type of token to create.
 * @param data The data associated with the token.
 * @return The token on success, 0 on failure.
 */
token * tok_new(tok_type type, string * data) {
  token * tok;
  if(0 == (tok = mem_alloc(sizeof(token)))) { return 0; }
  tok->type = type;
  tok->data = data;
  return tok;
}

/**
 * Delete a token.
 * @param tok The token to delete.
 */
void tok_delete(token * tok) {
  if(0 == tok) { return; }
  str_del(tok->data);
  mem_free(tok);
}

/**
 * Print a representation of a token to standard output.
 * @param tok The token.
 */
void tok_print(token * tok) {
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
