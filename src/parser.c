/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#include "parser.h"
#include "lexer.h"
#include "memory.h"

/* private function prototypes */

/* public function definitions */

parser * par_new(lexer * lex) {
  parser * par;
  if(0 == (par = mem_alloc(sizeof(* par)))) { return 0; }
  par->state = PAR_DEF;
  par->lex = lex;
  return par;
}

void par_del(parser * par) {
  if(0 == par) { return; }
  mem_free(par);
}

/* private function definitions */
