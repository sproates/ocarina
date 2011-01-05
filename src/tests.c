#include <stdio.h>
#include "string.h"
#include "lexer.h"
#include "token.h"
#include "memory.h"

int string_tests(void);
int lexer_tests(void);
void test_pass(void);
void test_fail(void);
int test_count(void);
int fail_count(void);
int pass_count(void);

int number_of_tests = 0;
int passed_tests = 0;
int failed_tests = 0;

void test_pass(void) {
  number_of_tests++;
  passed_tests++;
}

void test_fail(void) {
  number_of_tests++;
  failed_tests++;
}

int test_count(void) {
  return number_of_tests;
}

int fail_count(void) {
  return failed_tests;
}

int pass_count(void) {
  return passed_tests;
}

int main(void) {
  string_tests();
  lexer_tests();
  printf("\n\n----------------------------------\n\n");
  printf("Tests: %d\n", test_count());
  printf("Passed: %d\n", pass_count());
  printf("Failed: %d\n", fail_count());
  return (0 != fail_count());
}

int string_tests(void) {
  string * s;

  printf("Running string tests...\n");

  printf("string_new()\n");
  s = string_new("test string");
  if(0 == s) {
    printf("Failed to create new string\n");
    test_fail();
    return 1;
  }
  test_pass();
  if(11 != s->length) {
    printf("String length is incorrect\n");
    test_fail();
    return 1;
  }
  test_pass();

  printf("string_append()\n");
  if(0 == string_append(s, '!')) {
    printf("Append failed\n");
    test_fail();
    return 1;
  }
  test_pass();
  if(12 != s->length) {
    printf("String length is incorrect\n");
    test_fail();
  }
  test_pass();

  string_delete(s);
  s = string_new("test string 2");
  printf("string_equals()\n");
  if(!string_equals(s, s)) {
    printf("Strings have unequal length\n");
    test_fail();
  }
  test_pass();
  if(!string_equals_char(s, "test string 2")) {
    printf("Strings have unequal length\n");
    test_fail();
  }
  test_pass();
  string_delete(s);

  printf("Long strings\n");
  s = string_new("Lorem ipsum dolor sit amet, consectetur adipiscing elit. ");
  string_append_string(s, string_new("Cras iaculis, purus ac rhoncus ornare, diam quam aliquet nunc, sit amet hendrerit "));
  string_append_string(s, string_new("diam augue id nulla. Ut consequat leo et turpis tempus molestie. Nam eros mauris, imperdiet id auctor sed, venenatis sed tellus. "));
  string_append_string(s, string_new("Integer semper ullamcorper risus, ac porttitor libero adipiscing in. Praesent faucibus gravida augue at mollis. Maecenas aliquam, "));
  string_append_string(s, string_new("lectus malesuada pulvinar pretium, elit tellus facilisis eros, a mattis nisl purus quis mauris. Suspendisse sit amet eros dui, congue "));
  string_append_string(s, string_new("fermentum orci. Vivamus non magna vel nisl imperdiet euismod vel sed elit. Suspendisse dolor risus, dictum sit amet tempus tincidunt, "));
  string_append_string(s, string_new("ultricies sed diam. Mauris eu diam venenatis enim lacinia tempor. Vestibulum id posuere ligula. Donec ornare dictum lacus, in tempus "));
  string_append_string(s, string_new("augue scelerisque at. Phasellus blandit neque id odio ullamcorper sit amet imperdiet felis facilisis. Donec interdum, libero id placerat cursus, elit "));
  string_append_string(s, string_new("augue pharetra risus, varius bibendum lorem nibh id nibh. Integer rutrum lobortis neque in rutrum. Fusce sed purus non ligula imperdiet ornare ut ut velit. "));
  string_append_string(s, string_new("Sed vel fermentum lectus. Etiam a sapien quis justo vestibulum lacinia. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; "));
  string_append_string(s, string_new("Nam congue dictum ornare. Curabitur nec arcu mauris. Ut pulvinar elementum orci, non bibendum justo elementum vel. Suspendisse ultricies auctor arcu id "));
  string_append_string(s, string_new("vestibulum. Morbi felis eros, faucibus in tempor non, cursus quis tortor. Suspendisse erat odio, consequat ac adipiscing in, scelerisque sed magna. "));
  string_append_string(s, string_new("Morbi neque quam, scelerisque vitae aliquam nec, tincidunt nec metus. Mauris eu lacinia erat. Sed vestibulum rhoncus leo. Cras vulputate nunc a nisl "));
  string_append_string(s, string_new("tincidunt sed feugiat massa venenatis. Maecenas vel odio eros, ut bibendum velit. Pellentesque cursus semper metus, nec accumsan risus eleifend id. "));
  string_append_string(s, string_new("Pellentesque pretium urna et turpis condimentum ut placerat mauris euismod. Fusce id sapien in risus tincidunt ullamcorper vitae sit amet nibh. Vivamus "));
  string_append_string(s, string_new("ornare arcu sed sapien dignissim at pharetra ipsum sollicitudin. Vivamus eleifend arcu ut augue mollis dapibus. Aliquam id lobortis risus. Sed eu elit mi. "));
  string_append_string(s, string_new("In accumsan vulputate urna, ut lacinia nulla mattis ut. Nam tellus justo, auctor ac adipiscing ut, aliquet at lectus. Pellentesque augue leo, dapibus ac "));
  string_append_string(s, string_new("cursus ac, vulputate et libero. Morbi imperdiet, dolor et convallis malesuada, velit justo vulputate libero, sed volutpat mi metus nec purus. Aenean pellentesque iaculis nunc amet."));
  
  if(2502 != s->length) {
    printf("Long string has incorrect length\n");
    test_fail();
  }
  test_pass();

  printf("Completed string tests\n");
  return 0;
}

int lexer_tests(void) {
  FILE * script_file;
  lexer * lex;
  token * tok;

  printf("Running lexer tests...\n");

  if(0 == (script_file = fopen("test.oca", "r"))) {
    printf("Could not open source file for reading.\n");
    return 1;
  }
  printf("Opened script file\n");
  if(0 == (lex = lexer_new(script_file))) {
    printf("Unable to start lexing\n");
    return 1;
  }
  printf("Created lexer\n");
  while(1) {
    tok = lexer_next(lex);
    printf("Got token\n");
    token_print(tok);
    if(0 == tok || TOKEN_EOF == tok->type) {
      printf("Deleting token and exiting lexer\n");
      token_delete(tok);
      break;
    }
    printf("Deleting token\n");
    token_delete(tok);
    printf("Lexing...\n");
  }
  printf("Finished lexing\n");
  if(EOF == fclose(script_file)) {
    printf("Failed to close file handle on source file.\n");
    return 1;
  }
  printf("Closed source file\n");
  lexer_delete(lex);

  printf("Completed lexer tests\n");
  return 0;
}
