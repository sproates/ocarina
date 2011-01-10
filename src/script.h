#ifndef SCRIPT_H
#define SCRIPT_H

/* public structure definitions */

typedef enum {
  SCR_FILE,
  SCR_STR
} script_type;

typedef struct {
  script_type type;
} script;

/* public function prototypes */

script * scr_new(script_type type);
void scr_del(script * scr);

#endif
