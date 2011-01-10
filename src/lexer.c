#include "lexer.h"
#include "memory.h"
#include "token.h"
#include <stdio.h>

/* private function prototypes */

int _is_int(char c);
int _is_space(char c);
int _is_str_end(char c);
int _is_id(char c);
int _is_id_start(char c);
int _is_alpha(char c);
int _is_ctrl_char(char c);
int _is_keyword(string * s);
int _is_escapable(char c);
int _is_escape(char c);
char _lexer_next_char(lexer * lex);
char _make_escape(char c);
token * _token_ctrl_char(char c);
token * _tok_new(lexer * lex, tok_type type, lex_state state);
lexer * _lex_adv(lexer * lex);
lexer * _lex_set_state(lexer * lex, lex_state state);
lexer * _lex_set_char(lexer * lex, const char c);

/* public function definitions */

/**
 * Create a new lexer instance.
 *
 * @param script Handle to an open source file.
 *
 * @return A pointer to a lexer on success, zero on failure.
 */
lexer * lex_new(FILE * script) {
  lexer * lex;

  if(0 == (lex = mem_alloc(sizeof(* lex)))) {
    return 0;
  }
  lex->state = LEX_DEF;
  lex->script = script;
  lex->pos = 0;
  lex->max_buf = 1024;
  if(0 == (lex->buffer = mem_alloc(lex->max_buf * (sizeof(char))))) {
    return 0;
  }
  lex->buf_size = 0;
  lex->tok_buf = str_new(0);
  return lex;
}

/**
 * Destructs a lexer.
 *
 * @param lex The lexer to delete.
 */
void lex_del(lexer * lex) {
  if(0 != lex) {
    str_del(lex->tok_buf);
    mem_free(lex->buffer);
    mem_free(lex);
  }
}

/**
 * Obtains the next token from a lexer.
 *
 * @param lex The lexer from which to obtain a token.
 *
 * @return A token.
 */
token * lex_next(lexer * lex) {
  switch(lex->state) {
    case LEX_DEF:
      _lex_adv(lex);
      if(EOF == lex->current_char) {
        return lex_next(_lex_set_state(lex, LEX_DONE));
      } else if(_is_int(lex->current_char)) {
        return lex_next(_lex_set_state(lex, LEX_IN_INT));
      } else if(_is_space(lex->current_char)) {
        return lex_next(lex);
      } else if(_is_str_end(lex->current_char)) {
        return lex_next(_lex_adv(_lex_set_state(lex, LEX_IN_STR)));
      } else if(_is_id_start(lex->current_char)) {
        return lex_next(_lex_set_state(lex, LEX_IN_ID));
      } else if(_is_ctrl_char(lex->current_char)) {
        return _token_ctrl_char(lex->current_char);
        break;
      } else {
        return lex_next(_lex_set_state(lex, LEX_ERR));
      }
    case LEX_IN_INT:
      if(_is_int(lex->current_char)) {
        if(0 == str_add(lex->tok_buf, lex->current_char)) {
          return lex_next(_lex_set_state(lex, LEX_ERR));
        }
        return lex_next(_lex_adv(lex));
      }
      return _tok_new(lex, TOK_INT, LEX_DEF);
    case LEX_IN_ID:
      if(_is_id(lex->current_char)) {
        if(0 == str_add(lex->tok_buf, lex->current_char)) {
          return lex_next(_lex_set_state(lex, LEX_ERR));
        }
        return lex_next(_lex_adv(lex));
      }
      if(_is_keyword(lex->tok_buf)) {
        return _tok_new(lex, TOK_KEY, LEX_DEF);
      }
      return _tok_new(lex, TOK_ID, LEX_DEF);
    case LEX_IN_STR:
      if(!_is_str_end(lex->current_char)) {
        if(_is_escape(lex->current_char)) {
          return lex_next(_lex_adv(_lex_set_state(lex, LEX_IN_ESC)));
        }
        if(0 == str_add(lex->tok_buf, lex->current_char)) {
          return lex_next(_lex_set_state(lex, LEX_ERR));
        }
        return lex_next(_lex_adv(lex));
      }
      return _tok_new(lex, TOK_STR, LEX_DEF);
    case LEX_IN_ESC:
      if(_is_escapable(lex->current_char)) {
        _lex_set_char(lex, _make_escape(lex->current_char));
        if(0 == str_add(lex->tok_buf, lex->current_char)) {
          return lex_next(_lex_set_state(lex, LEX_ERR));
        }
        return lex_next(_lex_adv(_lex_set_state(lex, LEX_IN_STR)));
      }
      return lex_next(_lex_set_state(lex, LEX_ERR));
    case LEX_ERR:
      return _tok_new(lex, TOK_ERR, LEX_DEF);
    case LEX_DONE:
    default:
      return _tok_new(lex, TOK_EOF, LEX_DONE);
  }
  return 0;
}

/* private function definitions */

/**
 * Determine whether a char is an integer.
 *
 * @param c The char.
 *
 * @return 1 if it is, 0 if it isn't.
 */
int _is_int(char c) {
  return (
    '0' <= c &&
    '9' >= c
  );
}

/**
 * Determine whether a char is a whitespace.
 *
 * @param c The char.
 *
 * @return 1 if it is, 0 if it isn't.
 */
int _is_space(char c) {
  return (
    '\t' == c ||
    '\r' == c ||
    '\n' == c ||
    ' ' == c
  );
}

/**
 * Determine whether a char is a string delimiter.
 *
 * @param c The char.
 *
 * @return 1 if it is, 0 if it isn't.
 */
int _is_str_end(char c) {
  return ('"' == c);
}

/**
 * Determine whether a char is a letter of the alphabet i.e. [a-zA-Z]
 *
 * @param c The char.
 *
 * @return 1 if it is, 0 if it isn't.
 */
int _is_alpha(char c) {
  return (
    ('A' <= c && 'Z' >= c) ||
    ('a' <= c && 'z' >= c)
  );
}

/**
 * Determine whether a char is a valid character of an identifier.
 *
 * @param c The char.
 *
 * @return 1 if it is, 0 if it isn't.
 */
int _is_id(char c) {
  return (
    _is_alpha(c) ||
    _is_int(c) ||
    '_' == c
  );
}

/**
 * Determine whether a char is a valid starting character of an identifier.
 *
 * @param c The char.
 *
 * @return 1 if it is, 0 if it isn't.
 */
int _is_id_start(char c) {
  return (
    _is_alpha(c) ||
    '_' == c
  );
}

/**
 * Determine whether a char is a control character.
 *
 * @param c The char.
 *
 * @return 1 if the char is a control character, 0 if it isn't.
 */
int _is_ctrl_char(char c) {
  return (
    '(' == c ||
    ')' == c ||
    '[' == c ||
    ']' == c ||
    '{' == c ||
    '}' == c
  );
}

/**
 * Determine whether a string is a keyword.
 *
 * @param s The string.
 *
 * @return 1 if the string is a keyword, 0 if it isn't.
 */
int _is_keyword(string * s) {
  return (
    str_eq_char(s, "if") ||
    str_eq_char(s, "for")
  );
}

/**
 * Determine whether a character is escapable.
 *
 * @param c The character.
 *
 * @return Non-zero if the character is escapable, 0 if it isn't.
 */
int _is_escapable(char c) {
  return (
    'n' == c ||
    'r' == c ||
    't' == c ||
    '"' == c ||
    '\\' == c
  );
}

/**
 * Make an escaped character from a char.
 *
 * @param c The char.
 *
 * @return An escaped character.
 */
char _make_escape(char c) {
  switch(c) {
    case 'n':
      return '\n';
    case 'r':
      return '\r';
    case 't':
      return '\t';
    case '"':
    case '\\':
    default:
      return c;
      return c;
  }
}

/**
 * Determine whether a character is an escape character.
 *
 * @param c The character.
 *
 * @return Non-zero if the character is an escape character, 0 if it isn't.
 */
int _is_escape(char c) {
  return ('\\' == c);
}

/**
 * Construct a control type token from a char.
 *
 * @param c The char.
 *
 * @return The token on success, 0 on failure.
 */
token * _token_ctrl_char(char c) {
  tok_type type;
  switch(c) {
    case '}':
      type = TOK_CL_BC;
      break;
    case ']':
      type = TOK_CL_BK;
      break;
    case ')':
      type = TOK_CL_PA;
      break;
    case '[':
      type = TOK_OP_BK;
      break;
    case '{':
      type = TOK_OP_BC;
      break;
    case '(':
      type = TOK_OP_PA;
      break;
    default:
      type = TOK_ERR;
      break;
  }
  return tok_new(type, 0);
}

/**
 * Move a lexer onto its next input character.
 *
 * @param lex The lexer.
 *
 * @return The modified lexer.
 */
lexer * _lex_adv(lexer * lex) {
  return _lex_set_char(lex, _lexer_next_char(lex));
}

/**
 * Get the next character from a lexer.
 *
 * @param lex The lexer.
 *
 * @return char The next character from the lexer (EOF on end of file).
 */
char _lexer_next_char(lexer * lex) {
  if(0 == lex->buf_size || lex->pos >= lex->buf_size) {
    lex->buf_size = fread(lex->buffer, sizeof(char), lex->max_buf, lex->script);
    if(0 == lex->buf_size) {
      return EOF;
    }
  }
  return lex->buffer[lex->pos++];
}

/**
 * Set the state of a lexer.
 *
 * @param lex The lexer.
 * @param state The state.
 *
 * @return The modified lexer.
 */
lexer * _lex_set_state(lexer * lex, lex_state state) {
  if(lex) {
    lex->state = state;
  }
  return lex;
}

/**
 * Set the current char of a lexer.
 *
 * @param lex The lexer.
 * @param c The char.
 *
 * @return The lexer.
 */
lexer * _lex_set_char(lexer * lex, const char c) {
  if(lex) {
    lex->current_char = c;
  }
  return lex;
}

/**
 * Create a new token from a lexer, and leave the lexer in a given state.
 *
 * @param lex The lexer.
 * @param type The type of token to create.
 * @param state The state to leave the lexer in.
 *
 * @return The newly created token.
 */
token * _tok_new(lexer * lex, tok_type type, lex_state state) {
  token * t;
  if(lex) {
    t = tok_new(type, lex->tok_buf);
    lex->tok_buf = str_new(0);
    _lex_set_state(lex, state);
  }
  return t;
}
