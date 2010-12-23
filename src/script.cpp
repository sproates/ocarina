#include "script.h"
#include <iostream>

namespace ocarina {

  Script::Script(std::istream* source) {
    std::cout << "Script::Script()" << std::endl;
	this->source = source;
  }

  Script::~Script() {
    std::cout << "Script::~Script()" << std::endl;
  }
}
