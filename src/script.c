#include "script.h"
#include "memory.h"
#include "string.h"

/* private function prototypes */

script_impl * _scr_impl_new(void);
void _scr_impl_del(script_impl * impl);
void _scr_del_file(file_script * scr);
void _scr_del_str(string_script * scr);
file_script * _scr_new_file(const char * source);
string_script * _scr_new_str(const char * source);
char _scr_file_next(file_script * scr);
char _scr_str_next(string_script * scr);

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
  if(0 == (scr = mem_alloc(sizeof(script)))) {
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
      if(0 == (scr->impl->s = _scr_new_str(source))) {
        goto error;
      }
      break;
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
char scr_next(script * scr) {
  switch(scr->type) {
    case SCR_FILE:
      return _scr_file_next(scr->impl->f);
    case SCR_STR:
      return _scr_str_next(scr->impl->s);
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

/**
 * Destructs a file_script.
 *
 * @param scr The file_script to delete.
 */
void _scr_del_file(file_script * scr) {
  if(scr) {
    if(scr->f) {
      fclose(scr->f);
    }
    mem_free(scr->buf);
    mem_free(scr);
  }
}

/**
 * Destructs a string_script.
 *
 * @param scr The string_script to delete.
 */
void _scr_del_str(string_script * scr) {
  if(scr) {
    str_del(scr->s);
    mem_free(scr);
  }
}

/**
 * Construct a new string_script.
 *
 * @param source The source.
 *
 * @return A string_script on success, 0 on failure.
 */
string_script * _scr_new_str(const char * source) {
  string_script * scr;
  if(0 == (scr = mem_alloc(sizeof(string_script)))) {
    goto error;
  }
  if(0 == (scr->s = str_new(source))) {
    goto error;
  }
  scr->pos = 0;
  return scr;
  error:
    _scr_del_str(scr);
    return 0;
}

/**
 * Construct a new file_script.
 *
 * @param source The source file name.
 *
 * @return A file_script on success, 0 on failure.
 */
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
 * Get the next character from a file_script.
 *
 * @param scr The file_script.
 *
 * @return The next character.
 */
char _scr_file_next(file_script * scr) {
  if(0 == scr->buf_size || scr->pos >= scr->buf_size) {
    scr->buf_size = fread(scr->buf, sizeof(char), scr->max_buf, scr->f);
    if(0 == scr->buf_size) {
      return EOF;
    }
  }
  return scr->buf[scr->pos++];
}

/**
 * Get the next character from a string_script.
 *
 * @param scr The string_script.
 *
 * @return The next character.
 */
char _scr_str_next(string_script * scr) {
  char c;
  if(0 == (c = str_at(scr->s, scr->pos++))) {
    return EOF;
  }
  return c;
}
