#include "script.h"
#include "memory.h"
#include "string.h"

/* private function prototypes */

script_impl * _scr_impl_new(void);
void _scr_impl_del(script_impl * impl);
void _scr_del_file(file_script * scr);
file_script * _scr_new_file(const char * source);

/* public function definitions */

/**
 * Create a new script instance.
 *
 * @param type The type of script.
 *
 * @return A pointer to a script on success, zero on failure.
 */
script * scr_new(script_type type, const char * source) {
  script * scr;
  if(0 == (scr = mem_alloc(sizeof(script))) ||
     0 == (scr->impl = _scr_impl_new())) {
    goto error;
  }
  scr->type = type;
  switch(type) {
    case SCR_FILE:
      if(0 == (scr->impl->f = _scr_new_file(source))) {
        goto error;
      }
      break;
    case SCR_STR:
      scr->impl->s->s = str_new(source);
      if(0 == scr->impl->s->s) {
        goto error;
      }
      scr->impl->s->pos = 0;
      break;
    default:
      goto error;
  }
  return scr;
error:
  scr_del(scr);
  return 0;
}

file_script * _scr_new_file(const char * source) {
  file_script * scr;
  if(0 == (scr = mem_alloc(sizeof(file_script)))) {
    goto error;
  }
  scr->filename = source;
  if(0 == (scr->f = fopen(scr->filename, "r"))) {
    goto error;
  }
  scr->pos = 0;
  scr->max_buf = 1024;
  scr->buf_size = 0;
  if(0 == (scr->buf = mem_alloc(scr->max_buf * (sizeof(char))))) {
    goto error;
  }
  return scr;
error:
  _scr_del_file(scr);
  return 0;
}

/**
 * Destructs a script.
 *
 * @param scr The script to delete.
 */
void scr_del(script * scr) {
  if(0 != scr) {
    switch(scr->type) {
      case SCR_FILE:
        _scr_del_file(scr->impl->f);
        break;
      default:
        break;
    }
    mem_free(scr);
  }
}

/**
 * Get the next character from a script.
 *
 * @param scr The script.
 *
 * @return The next character.
 */
char scr_next_char(script * scr) {
  char c;
  switch(scr->type) {
    case SCR_FILE:
      if(0 == scr->impl->f->buf_size || scr->impl->f->pos >= scr->impl->f->buf_size) {
        scr->impl->f->buf_size = fread(scr->impl->f->buf, sizeof(char), scr->impl->f->max_buf, scr->impl->f->f);
        if(0 == scr->impl->f->buf_size) {
          return EOF;
        }
      }
      return scr->impl->f->buf[scr->impl->f->pos++];
    case SCR_STR:
      if(0 == (c = str_at(scr->impl->s->s, scr->impl->s->pos++))) {
        return EOF;
      }
      return c;
    default:
      return 0;
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

void _scr_del_file(file_script * scr) {
  if(scr) {
    if(scr->f) {
      fclose(scr->f);
    }
    mem_free(scr->buf);
    mem_free(scr);
  }
}