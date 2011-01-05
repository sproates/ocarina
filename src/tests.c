#include <stdio.h>
#include "string.h"
#include "lexer.h"
#include "token.h"
#include "memory.h"

int string_tests(void);
int lexer_tests(void);

int main(void) {
  int string_test_result, lexer_test_result;

  string_test_result = string_tests();
  lexer_test_result = lexer_tests();

  return string_test_result & lexer_test_result;
}

int string_tests(void) {
  printf("Running string tests...\n");
  printf("Completed string tests\n");
  return 0;
}

int lexer_tests(void) {
  printf("Running lexer tests...\n");
  printf("Completed lexer tests\n");
  return 0;
}
