%option noyywrap
%option c++

%{
#include <iostream>
%}

NONZERODIGIT [1-9]
DIGIT [0-9]

ALPHA [a-zA-Z]
ALPHANUMERIC [a-zA-Z0-9]

WHITESPACE [ \t\n]+

%%

{WHITESPACE}

"-"?{NONZERODIGIT}{DIGIT}* std::cout << "Integer: " << YYText() << std::endl;

"-"?{DIGIT}+"."{DIGIT}+ std::cout << "Real: " << YYText() << std::endl;

{ALPHA}+{ALPHANUMERIC}* std::cout << "Identifier: " << YYText() << std:: endl;

. {
  std::cout << "Unknown character: " << YYText() << std::endl;
  yyterminate();
}

%%
