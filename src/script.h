#ifndef OCARINA_SCRIPT_H
#define OCARINA_SCRIPT_H

namespace ocarina {

  class Script {
    public:
	  Script(std::istream* source);
	  ~Script;
	private:
	protected:
	  std::istream* source;
  }
}

#endif
