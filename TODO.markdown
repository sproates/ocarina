Implementation
--------------

* The parser should read tokens from the lexer.
    * Parser needs to maintain a queue of tokens.
* The lexer should provide meaningful error messages.
* The lexer should have a concept of line number and position.

Testing
-------

* Move tests into separate hierarchy.
* Implement unit tests for core functions.
* Add functional tests written in Ocarina.

Build
-----

* Refactor build system.
    * Be able to build from the root folder.
    * Use autoconf / automake.

Documentation
-------------

* Hand-maintained documentation should use markdown.
* Use doxygen to generate source documentation.
