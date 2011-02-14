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

    block             = [whitespace] , "{" , [whitespace] , { expression , [whitespace] } , "}" ;
    module            = "module" , [block] ;

    alpha             = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" ;
    identifier        = alpha , { alpha | digit } ;

    call              = identifier , param-list ;
    param             = natural | real | string | identifier ;
    param-list        = "(" , whitespace , ")" | "(" , whitespace , [{param , "," whitespace }] , param , whitespace , ")" ;
    func-definition   = "func" , whitespace , [identifier] , param-list , block ;

    expression        = func-definition | call

    program           = "main" , whitespace , "<-" , block ;
