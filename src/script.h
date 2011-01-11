#ifndef SCRIPT_H
#define SCRIPT_H

#include "string.h"
#include <stdio.h>

/* public structure definitions */

typedef struct {
  char * filename;
  FILE * f;
  char * buf;
  int buf_size;
  int max_buf;
  int pos;
} file_script;

typedef struct {
  string * s;
} string_script;

typedef enum {
  SCR_FILE,
  SCR_STR
} script_type;

typedef union {
  string_script * s;
  file_script * f;
} script_impl;

typedef struct {
  script_type type;
  script_impl * impl;
} script;

/* public function prototypes */

script * scr_new(script_type type, char * source);
void scr_del(script * scr);
char scr_next_char(script * scr);

#endif
