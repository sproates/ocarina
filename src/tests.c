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

  printf("str_new()\n");
  s = str_new("test string");
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

  printf("str_add()\n");
  if(0 == str_add(s, '!')) {
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

  str_del(s);
  s = str_new("test string 2");
  printf("str_eq()\n");
  if(!str_eq(s, s)) {
    printf("Strings have unequal length\n");
    test_fail();
  }
  test_pass();
  if(!str_eq_char(s, "test string 2")) {
    printf("Strings have unequal length\n");
    test_fail();
  }
  test_pass();
  str_del(s);

  printf("Long strings\n");
  s = str_new("Lorem ipsum dolor sit amet, consectetur adipiscing elit. ");
  str_add_str(s, str_new("Cras iaculis, purus ac rhoncus ornare, diam quam aliquet nunc, sit amet hendrerit "));
  str_add_str(s, str_new("diam augue id nulla. Ut consequat leo et turpis tempus molestie. Nam eros mauris, imperdiet id auctor sed, venenatis sed tellus. "));
  str_add_str(s, str_new("Integer semper ullamcorper risus, ac porttitor libero adipiscing in. Praesent faucibus gravida augue at mollis. Maecenas aliquam, "));
  str_add_str(s, str_new("lectus malesuada pulvinar pretium, elit tellus facilisis eros, a mattis nisl purus quis mauris. Suspendisse sit amet eros dui, congue "));
  str_add_str(s, str_new("fermentum orci. Vivamus non magna vel nisl imperdiet euismod vel sed elit. Suspendisse dolor risus, dictum sit amet tempus tincidunt, "));
  str_add_str(s, str_new("ultricies sed diam. Mauris eu diam venenatis enim lacinia tempor. Vestibulum id posuere ligula. Donec ornare dictum lacus, in tempus "));
  str_add_str(s, str_new("augue scelerisque at. Phasellus blandit neque id odio ullamcorper sit amet imperdiet felis facilisis. Donec interdum, libero id placerat cursus, elit "));
  str_add_str(s, str_new("augue pharetra risus, varius bibendum lorem nibh id nibh. Integer rutrum lobortis neque in rutrum. Fusce sed purus non ligula imperdiet ornare ut ut velit. "));
  str_add_str(s, str_new("Sed vel fermentum lectus. Etiam a sapien quis justo vestibulum lacinia. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; "));
  str_add_str(s, str_new("Nam congue dictum ornare. Curabitur nec arcu mauris. Ut pulvinar elementum orci, non bibendum justo elementum vel. Suspendisse ultricies auctor arcu id "));
  str_add_str(s, str_new("vestibulum. Morbi felis eros, faucibus in tempor non, cursus quis tortor. Suspendisse erat odio, consequat ac adipiscing in, scelerisque sed magna. "));
  str_add_str(s, str_new("Morbi neque quam, scelerisque vitae aliquam nec, tincidunt nec metus. Mauris eu lacinia erat. Sed vestibulum rhoncus leo. Cras vulputate nunc a nisl "));
  str_add_str(s, str_new("tincidunt sed feugiat massa venenatis. Maecenas vel odio eros, ut bibendum velit. Pellentesque cursus semper metus, nec accumsan risus eleifend id. "));
  str_add_str(s, str_new("Pellentesque pretium urna et turpis condimentum ut placerat mauris euismod. Fusce id sapien in risus tincidunt ullamcorper vitae sit amet nibh. Vivamus "));
  str_add_str(s, str_new("ornare arcu sed sapien dignissim at pharetra ipsum sollicitudin. Vivamus eleifend arcu ut augue mollis dapibus. Aliquam id lobortis risus. Sed eu elit mi. "));
  str_add_str(s, str_new("In accumsan vulputate urna, ut lacinia nulla mattis ut. Nam tellus justo, auctor ac adipiscing ut, aliquet at lectus. Pellentesque augue leo, dapibus ac "));
  str_add_str(s, str_new("cursus ac, vulputate et libero. Morbi imperdiet, dolor et convallis malesuada, velit justo vulputate libero, sed volutpat mi metus nec purus. Aenean pellentesque iaculis nunc amet."));
  
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
  if(0 == (lex = lex_new(script_file))) {
    printf("Unable to start lexing\n");
    return 1;
  }
  printf("Created lexer\n");
  while(1) {
    tok = lex_next(lex);
    printf("Got token\n");
    tok_print(tok);
    if(0 == tok || TOK_EOF == tok->type) {
      printf("Deleting token and exiting lexer\n");
      tok_delete(tok);
      break;
    }
    printf("Deleting token\n");
    tok_delete(tok);
    printf("Lexing...\n");
  }
  printf("Finished lexing\n");
  if(EOF == fclose(script_file)) {
    printf("Failed to close file handle on source file.\n");
    return 1;
  }
  printf("Closed source file\n");
  lex_del(lex);

  printf("Completed lexer tests\n");
  return 0;
}
