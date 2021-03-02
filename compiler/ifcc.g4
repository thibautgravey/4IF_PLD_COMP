grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' line* '}' ;

line: (decl | def | aff | RETURN expr) ';' ;

decl: TYPE VAR_NAME ;

def: TYPE aff ;

aff: VAR_NAME '=' expr ;

expr: CONST #const
    | VAR_NAME #var
    | expr '+' expr # add
    | expr '-' expr # less
    | expr '*' expr # mult
    | expr '/' expr # div
    | '(' expr ')' # par
;

RETURN : 'return' ;

TYPE : 'int' ;

CONST : [0-9]+ ;

VAR_NAME : [a-zA-Z_][\\w]*  ;

COMMENT : '/*' .*? '*/' -> skip ;

DIRECTIVE : '#' .*? '\n' -> skip ;

WS : [ \t\r\n] -> channel(HIDDEN);
