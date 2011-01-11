#ifndef SCRIPT_H
#define SCRIPT_H

#include "string.h"
#include <stdio.h>

/* public structure definitions */

typedef struct {
  const char * filename;
  FILE * f;
  char * buf;
  unsigned int buf_size;
  unsigned int max_buf;
  unsigned int pos;
} file_script;

typedef struct {
  string * s;
  int pos;
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

script * scr_new(script_type type, const char * source);
void scr_del(script * scr);
char scr_next_char(script * scr);

#endif
