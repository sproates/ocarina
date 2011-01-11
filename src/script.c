#include "script.h"
#include "memory.h"
#include "string.h"

/* private function prototypes */

file_script * _scr_new_file(const char * source);
string_script * _scr_new_str(const char * source);
char _scr_file_next(file_script * scr);
char _scr_str_next(string_script * scr);
void _scr_del_file(file_script * scr);
void _scr_del_str(string_script * scr);

/* public function definitions */

/**
 * Create a new script instance.
 * @param type The type of script.
 * @return A pointer to a script on success, zero on failure.
 */
script * scr_new(const script_type type, const char * source) {
  script * scr;
  if(0 == (scr = mem_alloc(sizeof(script)))) { goto error; }
  if(0 == (scr->impl = mem_alloc(sizeof(scr->impl)))) { goto error; }
  if(SCR_FILE == type && (0 == (scr->impl->f = _scr_new_file(source)))) { goto error; }
  if(SCR_STR == type && (0 == (scr->impl->s = _scr_new_str(source)))) { goto error; }
  scr->type = type;
  return scr;
error:
  scr_del(scr);
  return 0;
}

/**
 * Destructs a script.
 * @param scr The script to delete.
 */
void scr_del(script * scr) {
  if(0 == scr) { return; }
  if(SCR_FILE == scr->type) { _scr_del_file(scr->impl->f);}
  else if(SCR_STR == scr->type) { _scr_del_str(scr->impl->s); }
  else { return; }
  mem_free(scr->impl);
  mem_free(scr);
}

/**
 * Get the next character from a script.
 * @param scr The script.
 * @return The next character.
 */
char scr_next(script * scr) {
  if(SCR_FILE == scr->type) { return _scr_file_next(scr->impl->f); }
  else if(SCR_STR == scr->type) { return _scr_str_next(scr->impl->s); }
  return 0;
}

/* private function definitions */

/**
 * Destructs a file_script.
 * @param scr The file_script to delete.
 */
void _scr_del_file(file_script * scr) {
  if(!scr) { return; }
  if(scr->f) { fclose(scr->f); }
  mem_free(scr);
}

/**
 * Destructs a string_script.
 * @param scr The string_script to delete.
 */
void _scr_del_str(string_script * scr) {
  if(!scr) { return; }
  str_del(scr->s);
  mem_free(scr);
}

/**
 * Construct a new string_script.
 * @param source The source.
 * @return A string_script on success, 0 on failure.
 */
string_script * _scr_new_str(const char * source) {
  string_script * scr;
  if(0 == (scr = mem_alloc(sizeof(file_script)))) { goto error; }
  if(0 == (scr->s = str_new(source))) { goto error; }
  scr->pos = 0;
  return scr;
error:
  _scr_del_str(scr);
  return 0;
}

/**
 * Construct a new file_script.
 * @param source The source file name.
 * @return A file_script on success, 0 on failure.
 */
file_script * _scr_new_file(const char * source) {
  file_script * scr;
  if(0 == (scr = mem_alloc(sizeof(file_script)))) { goto error; }
  if(0 == (scr->f = fopen(source, "r"))) { goto error; }
  scr->filename = source;
  scr->pos = scr->buf_size = 0;
  scr->max_buf = 1024;
  if(0 == (scr->buf = mem_alloc(scr->max_buf * (sizeof(char))))) { goto error; }
  return scr;
error:
  _scr_del_file(scr);
  return 0;
}

/**
 * Get the next character from a file_script.
 * @param scr The file_script.
 * @return The next character.
 */
char _scr_file_next(file_script * scr) {
  if(0 == scr->buf_size || scr->pos >= scr->buf_size) {
    scr->buf_size = fread(scr->buf, sizeof(char), scr->max_buf, scr->f);
    if(0 == scr->buf_size) { return EOF; }
  }
  return scr->buf[scr->pos++];
}

/**
 * Get the next character from a string_script.
 * @param scr The string_script.
 * @return The next character.
 */
char _scr_str_next(string_script * scr) {
  char c;
  return (0 != (c = str_at(scr->s, scr->pos++))) ? c : EOF;
}
