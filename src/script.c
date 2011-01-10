#include "script.h"
#include "memory.h"
#include "string.h"

/* private function prototypes */

script_impl * _scr_impl_new(void);
void _scr_impl_del(script_impl * impl);
void _str_scr_del(script * s);

/* public function definitions */

/**
 * Create a new script instance.
 *
 * @param type The type of script.
 *
 * @return A pointer to a script on success, zero on failure.
 */
script * scr_new(script_type type, char * source) {
  script * scr;
  if(0 == (scr = mem_alloc(sizeof(script))) ||
     0 == (scr->impl = _scr_impl_new())) {
    goto error;
  }
  scr->type = type;
  switch(type) {
    case SCR_FILE:
      scr->impl->f->filename = source;
      break;
    case SCR_STR:
      scr->impl->s->s = str_new(source);
      if(0 == scr->impl->s->s) {
        goto error;
      }
      break;
    default:
      goto error;
  }
  return scr;
error:
  scr_del(scr);
  return 0;
}

/**
 * Destructs a script.
 *
 * @param scr The script to delete.
 */
void scr_del(script * scr) {
  if(0 != scr) {
    _scr_impl_del(scr->impl);
    mem_free(scr);
  }
}

/* private function definitions */

/**
 * Create a new script_impl instance.
 *
 * @return A pointer to a script_impl on success, zero on failure.
 */
script_impl * _scr_impl_new(void) {
  script_impl * impl;
  if(0 == (impl = mem_alloc(sizeof(script_impl)))) {
    return 0;
  }
  return impl;
}

/**
 * Destructs a script_impl.
 *
 * @param scr The script_impl to delete.
 */
void _scr_impl_del(script_impl * impl)  {
  if(0 != impl) {
    mem_free(impl);
  }
}
