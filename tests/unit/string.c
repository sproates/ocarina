/* Copyright 2011 Ian Sproates <ian@sproates.net> */

/**
 * @file string.c
 * String unit tests.
 */

#include "string.h"
#include "unit_tests.h"

/* public function prototypes */

/**
 * Run the tests for the string functions.
 */
void string_tests(void);

/* public function definitions */

void string_tests(void) {
  string * s;
  char c;

  printf("Running string tests...\n");

  printf("str_new()\n");
  s = str_new("test string");
  if(0 == s) {
    printf("Failed to create new string\n");
    test_fail();
    return;
  }
  test_pass();
  if(11 != s->length) {
    printf("String length is incorrect\n");
    test_fail();
    return;
  }
  test_pass();

  printf("str_add()\n");
  if(0 == str_add(s, '!')) {
    printf("Append failed\n");
    test_fail();
    return;
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
  str_add_str(s, str_new("Cras iaculis, purus ac rhoncus ornare, diam quam "));
  str_add_str(s, str_new("aliquet nunc, sit amet hendrerit diam augue id "));
  str_add_str(s, str_new("nulla. Ut consequat leo et turpis tempus molestie."));
  str_add_str(s, str_new("  Nam eros mauris, imperdiet id auctor sed, "));
  str_add_str(s, str_new("venenatis sed tellus. Integer semper ullamcorper "));
  str_add_str(s, str_new("risus, ac porttitor libero adipiscing in. "));
  str_add_str(s, str_new("Praesent faucibus gravida augue at mollis. "));
  str_add_str(s, str_new("Maecenas aliquam, lectus malesuada pulvinar "));
  str_add_str(s, str_new("pretium, elit tellus facilisis eros, a mattis "));
  str_add_str(s, str_new("nisl purus quis mauris. Suspendisse sit amet eros "));
  str_add_str(s, str_new("dui, congue fermentum orci. Vivamus non magna vel "));
  str_add_str(s, str_new("nisl imperdiet euismod vel sed elit. Suspendisse "));
  str_add_str(s, str_new("dolor risus, dictum sit amet tempus tincidunt, "));
  str_add_str(s, str_new("ultricies sed diam. Mauris eu diam venenatis enim"));
  str_add_str(s, str_new("  lacinia tempor. Vestibulum id posuere ligula. "));
  str_add_str(s, str_new("Donec ornare dictum lacus, in tempus augue "));
  str_add_str(s, str_new("scelerisque at. Phasellus blandit neque id odio "));
  str_add_str(s, str_new("ullamcorper sit amet imperdiet felis facilisis. "));
  str_add_str(s, str_new("Donec interdum, libero id placerat cursus, elit "));
  str_add_str(s, str_new("augue pharetra risus, varius bibendum lorem nibh "));
  str_add_str(s, str_new("id nibh. Integer rutrum lobortis neque in rutrum. "));
  str_add_str(s, str_new("Fusce sed purus non ligula imperdiet ornare ut ut "));
  str_add_str(s, str_new("velit. Sed vel fermentum lectus. Etiam a sapien "));
  str_add_str(s, str_new("quis justo vestibulum lacinia. Vestibulum ante "));
  str_add_str(s, str_new("ipsum primis in faucibus orci luctus et ultrices "));
  str_add_str(s, str_new("posuere cubilia Curae; Nam congue dictum ornare. "));
  str_add_str(s, str_new("Curabitur nec arcu mauris. Ut pulvinar elementum "));
  str_add_str(s, str_new("orci, non bibendum justo elementum vel. "));
  str_add_str(s, str_new("Suspendisse ultricies auctor arcu id vestibulum. "));
  str_add_str(s, str_new("Morbi felis eros, faucibus in tempor non, cursus "));
  str_add_str(s, str_new("quis tortor. Suspendisse erat odio, consequat ac "));
  str_add_str(s, str_new("adipiscing in, scelerisque sed magna. Morbi neque "));
  str_add_str(s, str_new("quam, scelerisque vitae aliquam nec, tincidunt "));
  str_add_str(s, str_new("nec metus. Mauris eu lacinia erat. Sed vestibulum "));
  str_add_str(s, str_new("rhoncus leo. Cras vulputate nunc a nisl tincidunt "));
  str_add_str(s, str_new("sed feugiat massa venenatis. Maecenas vel odio "));
  str_add_str(s, str_new("eros, ut bibendum velit. Pellentesque cursus "));
  str_add_str(s, str_new("semper metus, nec accumsan risus eleifend id. "));
  str_add_str(s, str_new("Pellentesque pretium urna et turpis condimentum "));
  str_add_str(s, str_new("ut placerat mauris euismod. Fusce id sapien in "));
  str_add_str(s, str_new("risus tincidunt ullamcorper vitae sit amet nibh. "));
  str_add_str(s, str_new("Vivamus ornare arcu sed sapien dignissim at "));
  str_add_str(s, str_new("pharetra ipsum sollicitudin. Vivamus eleifend "));
  str_add_str(s, str_new("arcu ut augue mollis dapibus. Aliquam id lobortis "));
  str_add_str(s, str_new("risus. Sed eu elit mi. In accumsan vulputate urna,"));
  str_add_str(s, str_new("  ut lacinia nulla mattis ut. Nam tellus justo, "));
  str_add_str(s, str_new("auctor ac adipiscing ut, aliquet at lectus. "));
  str_add_str(s, str_new("Pellentesque augue leo, dapibus ac cursus ac, "));
  str_add_str(s, str_new("vulputate et libero. Morbi imperdiet, dolor et "));
  str_add_str(s, str_new("convallis malesuada, velit justo vulputate libero"));
  str_add_str(s, str_new(", sed volutpat mi metus nec purus. Aenean "));
  str_add_str(s, str_new("pellentesque iaculis nunc amet."));
  
  if(2505 != s->length) {
    printf("Long string has incorrect length: %d\n", s->length);
    test_fail();
  }
  test_pass();
  str_del(s);

  s = str_new("abc");

  printf("str_at()\n");
  if('a' != (c = str_at(s, 0))) {
    printf("Wrong char came back from str_at()\n");
    test_fail();
  }
  test_pass();
  if('b' != (c = str_at(s, 1))) {
    printf("Wrong char came back from str_at(): %c\n", c);
    test_fail();
  }
  test_pass();
  if('c' != (c = str_at(s, 2))) {
    printf("Wrong char came back from str_at(): %c\n", c);
    test_fail();
  }
  test_pass();
  if(0 != (c = str_at(s, 3))) {
    printf("Wrong char came back from str_at()%c\n", c);
    test_fail();
  }
  test_pass();
  if(0 != (c = str_at(s, 1050))) {
    printf("Wrong char came back from str_at()%c\n", c);
    test_fail();
  }
  test_pass();
  str_del(s);

  printf("Completed string tests\n");
}
