%option noyywrap
%option c++

%{

#include <iostream>

%}

NONZERODIGIT [1-9]
DIGIT [0|NONZERODIGIT]
INTEGER "-"?{NONZERODIGIT}{DIGIT}+
REAL "-"{INTEGER}"."{INTEGER}

ALPHA [a-zA-Z]

WHITESPACE [ \t]+

%%

{WHITESPACE}

{INTEGER} std::cout << "Integer: " << YYText() << std::endl;

{REAL} std::cout << "Real: " << YYText() << std::endl;

{ALPHA} std::cout << "Alpha: " << YYText() << std::endl;

. {
  std::cout << "Unknown character or sequence: " << YYText() << std::endl;
  yyterminate();
}

%%
