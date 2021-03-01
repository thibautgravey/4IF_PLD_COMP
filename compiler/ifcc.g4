grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' line* '}' ;

line: (decl | def | aff | RETURN expr) ';' ;

decl: TYPE VAR_NAME ;

def: TYPE aff ;

aff: VAR_NAME '=' (CONST | VAR_NAME) ;

expr: CONST | VAR_NAME ;

RETURN : 'return' ;

TYPE : 'int' ;

CONST : [0-9]+ ;

VAR_NAME : [a-zA-Z_][\\w]*  ;

COMMENT : '/*' .*? '*/' -> skip ;

DIRECTIVE : '#' .*? '\n' -> skip ;

WS : [ \t\r\n] -> channel(HIDDEN);
