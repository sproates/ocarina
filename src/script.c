#include "script.h"
#include "memory.h"

/* public function definitions */

/**
 * Create a new script instance.
 *
 * @param type The type of script.
 *
 * @return A pointer to a script on success, zero on failure.
 */
script * scr_new(script_type type) {
  script * scr;
  if(0 == (scr = mem_alloc(sizeof(script)))) {
    return 0;
  }
  scr->type = type;
  return scr;
}

/**
 * Destructs a script.
 *
 * @param scr The script to delete.
 */
void scr_del(script * scr) {
  if(0 != scr) {
    mem_free(scr);
  }
}
