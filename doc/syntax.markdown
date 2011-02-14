Ocarina syntax
--------------

    zero              = "0" ;
    non-zero-digit    = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
    digit             = zero | non-zero-digit ;
    
    natural           = non-zero-digit , { digit } ;
    integer           = zero | [ "-" ] , natural ;
    real              = zero | [ "-" ] , integer , [ "." ] , integer ;
    
    whitespace        = ? white space characters ? ;
    all-chars         = ? all printable characters ? ;

    string-delim      = '"' ;
    string            = string-delim , { all-chars - string-delim } , string-delim ;

    block             = [whitespace] , "{" , [whitespace] , { statement , [whitespace] } , "}" ;
    module            = "module" , [block] ;
    expression        = declaration | call;

    alpha             = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" ;
    identifier        = alpha , { alpha | digit } ;

    declaration       = identifier , [whitespace] , "<-" , [whitespace] | expression ;
    call              = identifier , param-list ;
    param             = natural | real | string | identifier ;
    param-list        = "(", ")" | "(" , [{param , "," }] , param , ")" ;
