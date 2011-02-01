Implementation
--------------

* The parser should read tokens from the lexer.
    * Parser needs to maintain a queue of tokens.
* The lexer should provide meaningful error messages.
* The lexer should have a concept of line number and position.

Testing
-------

* Implement unit tests for core functions.
* Add functional tests written in Ocarina.

Build
-----

  * Use autoconf / automake?
  * Add ability to build from alternative directories (to avoid clutter in
    the source directory).
