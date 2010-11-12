#ifndef OCARINA_LEXER_H
#define OCARINA_LEXER_H

#include <iostream>

namespace ocarina {

  class Lexer : public OcarinaFlexLexer {
    public:
      Lexer(std::istream* in = 0, std::ostream* out = 0);
      virtual ~Lexer();
    private:
  };
}

#endif
